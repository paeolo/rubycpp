#include "dma.h"
#include "File.h"
#include "gbfs.h"

#include <gba_types.h>

extern GBFS_FILE _4bpp_gbfs;
extern GBFS_FILE _8bpp_gbfs;
extern GBFS_FILE gbapal_gbfs;
extern GBFS_FILE gbabg_gbfs;
extern GBFS_FILE json_gbfs;

static const GBFS_FILE* _gbfs[] =
{
    &_4bpp_gbfs,
    &_8bpp_gbfs,
    &gbapal_gbfs,
    &gbabg_gbfs,
    &json_gbfs
};

File::File(const char* fileName, const int fileType)
{
    this->_data = gbfs_get_obj(_gbfs[fileType], fileName, &this->_size);
}

void File::copyTo(volatile void* location)
{
    dma::Copy16(3, this->_data, location, this->_size);
}

const bool File::exists()
{
    return (bool) this->_data;
}
const void* File::data()
{
    return this->_data;
}
const u32 File::size()
{
    return this->_size;
}
