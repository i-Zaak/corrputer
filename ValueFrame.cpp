/* 
 * ValueFrame
 * 
 * @author David Nemecek <dejvino at gmail dot com>
 */

#include "ValueFrame.h"

ValueFrame::ValueFrame(int dim, int size, float* data) {
    this->dim = dim;
    this->size = size;
    this->data = data;
}

ValueFrame::ValueFrame(const ValueFrame& orig) {
}

ValueFrame::~ValueFrame() {
}

