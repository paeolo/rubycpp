#include "Fixed.h"
#include "trig.h"

Fixed Sin(int index)
{
    return sine_[(u8) index];
}

Fixed Cos(int index)
{
    return sine_[(u8) (index + 64)];
}

/* -----------------------------------------*/
/* ---  Look-up Table of Q8.8 values   -----*/
/* -----------------------------------------*/
/* --  SIN(x*(PI/128)) for x in [0, 255]  --*/
/* -----------------------------------------*/

const Fixed sine_[] =
{
    Fixed(0),
    Fixed(0.0234375),
    Fixed(0.046875),
    Fixed(0.0703125),
    Fixed(0.09765625),
    Fixed(0.12109375),
    Fixed(0.14453125),
    Fixed(0.16796875),
    Fixed(0.19140625),
    Fixed(0.21875),
    Fixed(0.2421875),
    Fixed(0.265625),
    Fixed(0.2890625),
    Fixed(0.3125),
    Fixed(0.3359375),
    Fixed(0.359375),
    Fixed(0.37890625),
    Fixed(0.40234375),
    Fixed(0.42578125),
    Fixed(0.44921875),
    Fixed(0.46875),
    Fixed(0.4921875),
    Fixed(0.51171875),
    Fixed(0.53125),
    Fixed(0.5546875),
    Fixed(0.57421875),
    Fixed(0.59375),
    Fixed(0.61328125),
    Fixed(0.6328125),
    Fixed(0.65234375),
    Fixed(0.66796875),
    Fixed(0.6875),
    Fixed(0.70703125),
    Fixed(0.72265625),
    Fixed(0.73828125),
    Fixed(0.75390625),
    Fixed(0.76953125),
    Fixed(0.78515625),
    Fixed(0.80078125),
    Fixed(0.81640625),
    Fixed(0.828125),
    Fixed(0.84375),
    Fixed(0.85546875),
    Fixed(0.8671875),
    Fixed(0.87890625),
    Fixed(0.890625),
    Fixed(0.90234375),
    Fixed(0.9140625),
    Fixed(0.921875),
    Fixed(0.9296875),
    Fixed(0.94140625),
    Fixed(0.94921875),
    Fixed(0.953125),
    Fixed(0.9609375),
    Fixed(0.96875),
    Fixed(0.97265625),
    Fixed(0.98046875),
    Fixed(0.984375),
    Fixed(0.98828125),
    Fixed(0.9921875),
    Fixed(0.9921875),
    Fixed(0.99609375),
    Fixed(0.99609375),
    Fixed(0.99609375),
    Fixed(1),
    Fixed(0.99609375),
    Fixed(0.99609375),
    Fixed(0.99609375),
    Fixed(0.9921875),
    Fixed(0.9921875),
    Fixed(0.98828125),
    Fixed(0.984375),
    Fixed(0.98046875),
    Fixed(0.97265625),
    Fixed(0.96875),
    Fixed(0.9609375),
    Fixed(0.953125),
    Fixed(0.94921875),
    Fixed(0.94140625),
    Fixed(0.9296875),
    Fixed(0.921875),
    Fixed(0.9140625),
    Fixed(0.90234375),
    Fixed(0.890625),
    Fixed(0.87890625),
    Fixed(0.8671875),
    Fixed(0.85546875),
    Fixed(0.84375),
    Fixed(0.828125),
    Fixed(0.81640625),
    Fixed(0.80078125),
    Fixed(0.78515625),
    Fixed(0.76953125),
    Fixed(0.75390625),
    Fixed(0.73828125),
    Fixed(0.72265625),
    Fixed(0.70703125),
    Fixed(0.6875),
    Fixed(0.66796875),
    Fixed(0.65234375),
    Fixed(0.6328125),
    Fixed(0.61328125),
    Fixed(0.59375),
    Fixed(0.57421875),
    Fixed(0.5546875),
    Fixed(0.53125),
    Fixed(0.51171875),
    Fixed(0.4921875),
    Fixed(0.46875),
    Fixed(0.44921875),
    Fixed(0.42578125),
    Fixed(0.40234375),
    Fixed(0.37890625),
    Fixed(0.359375),
    Fixed(0.3359375),
    Fixed(0.3125),
    Fixed(0.2890625),
    Fixed(0.265625),
    Fixed(0.2421875),
    Fixed(0.21875),
    Fixed(0.19140625),
    Fixed(0.16796875),
    Fixed(0.14453125),
    Fixed(0.12109375),
    Fixed(0.09765625),
    Fixed(0.0703125),
    Fixed(0.046875),
    Fixed(0.0234375),
    Fixed(0),
    Fixed(-0.0234375),
    Fixed(-0.046875),
    Fixed(-0.0703125),
    Fixed(-0.09765625),
    Fixed(-0.12109375),
    Fixed(-0.14453125),
    Fixed(-0.16796875),
    Fixed(-0.19140625),
    Fixed(-0.21875),
    Fixed(-0.2421875),
    Fixed(-0.265625),
    Fixed(-0.2890625),
    Fixed(-0.3125),
    Fixed(-0.3359375),
    Fixed(-0.359375),
    Fixed(-0.37890625),
    Fixed(-0.40234375),
    Fixed(-0.42578125),
    Fixed(-0.44921875),
    Fixed(-0.46875),
    Fixed(-0.4921875),
    Fixed(-0.51171875),
    Fixed(-0.53125),
    Fixed(-0.5546875),
    Fixed(-0.57421875),
    Fixed(-0.59375),
    Fixed(-0.61328125),
    Fixed(-0.6328125),
    Fixed(-0.65234375),
    Fixed(-0.66796875),
    Fixed(-0.6875),
    Fixed(-0.70703125),
    Fixed(-0.72265625),
    Fixed(-0.73828125),
    Fixed(-0.75390625),
    Fixed(-0.76953125),
    Fixed(-0.78515625),
    Fixed(-0.80078125),
    Fixed(-0.81640625),
    Fixed(-0.828125),
    Fixed(-0.84375),
    Fixed(-0.85546875),
    Fixed(-0.8671875),
    Fixed(-0.87890625),
    Fixed(-0.890625),
    Fixed(-0.90234375),
    Fixed(-0.9140625),
    Fixed(-0.921875),
    Fixed(-0.9296875),
    Fixed(-0.94140625),
    Fixed(-0.94921875),
    Fixed(-0.953125),
    Fixed(-0.9609375),
    Fixed(-0.96875),
    Fixed(-0.97265625),
    Fixed(-0.98046875),
    Fixed(-0.984375),
    Fixed(-0.98828125),
    Fixed(-0.9921875),
    Fixed(-0.9921875),
    Fixed(-0.99609375),
    Fixed(-0.99609375),
    Fixed(-0.99609375),
    Fixed(-1),
    Fixed(-0.99609375),
    Fixed(-0.99609375),
    Fixed(-0.99609375),
    Fixed(-0.9921875),
    Fixed(-0.9921875),
    Fixed(-0.98828125),
    Fixed(-0.984375),
    Fixed(-0.98046875),
    Fixed(-0.97265625),
    Fixed(-0.96875),
    Fixed(-0.9609375),
    Fixed(-0.953125),
    Fixed(-0.94921875),
    Fixed(-0.94140625),
    Fixed(-0.9296875),
    Fixed(-0.921875),
    Fixed(-0.9140625),
    Fixed(-0.90234375),
    Fixed(-0.890625),
    Fixed(-0.87890625),
    Fixed(-0.8671875),
    Fixed(-0.85546875),
    Fixed(-0.84375),
    Fixed(-0.828125),
    Fixed(-0.81640625),
    Fixed(-0.80078125),
    Fixed(-0.78515625),
    Fixed(-0.76953125),
    Fixed(-0.75390625),
    Fixed(-0.73828125),
    Fixed(-0.72265625),
    Fixed(-0.70703125),
    Fixed(-0.6875),
    Fixed(-0.66796875),
    Fixed(-0.65234375),
    Fixed(-0.6328125),
    Fixed(-0.61328125),
    Fixed(-0.59375),
    Fixed(-0.57421875),
    Fixed(-0.5546875),
    Fixed(-0.53125),
    Fixed(-0.51171875),
    Fixed(-0.4921875),
    Fixed(-0.46875),
    Fixed(-0.44921875),
    Fixed(-0.42578125),
    Fixed(-0.40234375),
    Fixed(-0.37890625),
    Fixed(-0.359375),
    Fixed(-0.3359375),
    Fixed(-0.3125),
    Fixed(-0.2890625),
    Fixed(-0.265625),
    Fixed(-0.2421875),
    Fixed(-0.21875),
    Fixed(-0.19140625),
    Fixed(-0.16796875),
    Fixed(-0.14453125),
    Fixed(-0.12109375),
    Fixed(-0.09765625),
    Fixed(-0.0703125),
    Fixed(-0.046875),
    Fixed(-0.0234375)
};