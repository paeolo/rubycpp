#include "dma.h"
#include "File.h"
#include "Palette.h"

EWRAM_DATA Color Palette::data[PALETTE_LENGTH];
EWRAM_DATA Color Palette::buffer[PALETTE_LENGTH];

Color Color::Integer(int i)
{
    Color color;
    color.red = i & 31;
    color.green = (i >> 5) & 31;
    color.blue = (i >> 10) & 31;
    return color;
}
Color Color::centroid(Color const& x, Color const& y, int fader)
{
    Color color;
    color.red = ((32 - fader)*x.red + fader*y.red) >> 5;
    color.green = ((32 - fader)*x.green + fader*y.green) >> 5;
    color.blue = ((32 - fader)*x.blue + fader*y.blue) >> 5;
    return color;
}

void Palette::Copy(int source, int destination, int offset)
{
    dma::Copy16
    (
        3,
        &Palette::buffer[16*source],
        &Palette::buffer[16*destination + offset],
        32 - 2*offset
    );
}

void Palette::LoadToData(const char* paletteName, int position)
{
    File file(paletteName, FileType::GBAPAL);
    if(file.exists())
        file.copyTo(&Palette::data[16*position]);
}

void Palette::LoadToBuffer(const char* paletteName, int position)
{
    File file(paletteName, FileType::GBAPAL);
    if(file.exists())
        file.copyTo(&Palette::buffer[16*position]);
}

void Palette::FillData(const Color color)
{
    dma::Fill16(3, color, Palette::data, PALETTE_SIZE);
}

void Palette::FillBuffer(const Color color)
{
    dma::Fill16(3, color, Palette::buffer, PALETTE_SIZE);
}

void Palette::Flush()
{
    dma::Copy16(3, Palette::buffer, &PALETTE, PALETTE_SIZE);
}