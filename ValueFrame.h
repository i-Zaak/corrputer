/* 
 * ValueFrame
 * 
 * @author David Nemecek <dejvino at gmail dot com>
 */

#ifndef VALUEFRAME_H
#define	VALUEFRAME_H

class ValueFrame {
public:
    ValueFrame(int dim, int size, float* data);
    ValueFrame(const ValueFrame& orig);
    virtual ~ValueFrame();
    
    int getDim() {
        return this->dim;
    }
    
    int getSize() {
        return this->size;
    }
    
    float* getData() {
        return this->data;
    }
    
private:
    int dim;
    int size;
    float* data;
};

#endif	/* VALUEFRAME_H */

