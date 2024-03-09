/**
 * @file imageop.cpp
 * @brief Fichero con definiciones para el resto de métodos de la clase Image
 */

#include <iostream>
#include <cmath>

#include <image.h>
//#include <imageIO.h>

using namespace std;

Image Image::Crop(int nrow, int ncol, int height, int width) const {
    bool rowc = (0<=nrow) && (nrow<this->get_rows());
    bool colc = (0<=ncol) && (ncol<this->get_cols());
    bool heightc = (0<height) && (height<this->get_rows()-nrow);
    bool widthc = (0<=width) && (width<this->get_cols()-ncol);
    if(!(rowc && colc && heightc && widthc)) {
        throw std::invalid_argument("Wrong arguments at Crop");
    }

    Image im(height,width);
    for (int i=0; i<height; ++i)
        for (int j=0; j<width; ++j)
            im.set_pixel(i,j,this->get_pixel(i+nrow,j+ncol));

    return im;
}

Image Image::Zoom2X() const
{
    Image resultado(2*get_rows()-1,2*get_cols()-1);

    // Añadimos en su nueva posición a los píxeles de la imagen original
    for(int i=0; i < get_rows(); i++){
        for(int j=0; j < get_cols(); j++)
            resultado.set_pixel(2 * i, 2 * j, get_pixel(i, j));
    }

    // Rellenamos las columnas impares
    for(int i=0; i < resultado.get_rows(); i+=2){
        for(int j=1; j < resultado.get_cols(); j+=2)
            resultado.set_pixel(i,j,round((resultado.get_pixel(i,j-1)+resultado.get_pixel(i,j+1))/2.0));
    }

    // Rellenamos el resto
    for(int i=1; i < resultado.get_rows(); i+=2){
        for(int j=0; j < resultado.get_cols(); j++) {

            if(j%2 == 0) {
                resultado.set_pixel(i, j, round((resultado.get_pixel(i-1, j) +
                                                 resultado.get_pixel(i+1, j)) / 2.0));
            }
            else {
                resultado.set_pixel(i, j, round((resultado.get_pixel(i-1, j-1 )
                                                 + resultado.get_pixel(i-1,j+1)+resultado.get_pixel(i+1,j-1)+
                                                 resultado.get_pixel(i+1,j+1)) / 4.0));
            }
        }
    }

    return resultado;
}

double Image::Mean(int i, int j, int height, int width) const {
    //COMPROBAMOS LAS PRECONDICIONES

    if (i < 0 || i >= this->get_rows())
        throw std::invalid_argument("Wrong index 'i' in Mean");

    if (0 > j || j >= this->get_cols())
        throw std::invalid_argument("Wrong index 'j' in Mean");

    if (0 >= height+i || height+i > this->get_rows())
        throw std::invalid_argument("Wrong height in Mean");

    if (0 >= width+j || width+j > this->get_cols())
        throw std::invalid_argument("Wrong width in Mean");

    int suma = 0;

    for (int f=0; f<height; ++f)
        for (int c=0; c<width; ++c)
            suma+=this->get_pixel(f+i,c+j);

    double media = (1.0 * suma)/((double)height*(double)width);
    return media;
}

Image Image::Subsample(int factor) const {
    if(factor<=0 || factor>this->get_rows() || factor>this->get_cols())
        throw std::invalid_argument("Wrong factor in Subsample");

    if(factor==1)
        return *this;

    int filn=this->get_rows()/factor;
    int coln=this->get_cols()/factor;

    Image im(filn,coln);

    for(int i = 0; i < filn; ++i){
        for (int j = 0; j < coln; ++j) {
            byte pixel = round(Mean(i * factor, j* factor, factor, factor));
            im.set_pixel(i,j,pixel);
        }
    }

    return im;
}

void Image::AdjustContrast(byte in1, byte in2, byte out1, byte out2) {

    const int MAX_VALUE=255;

    bool in1c = (0>in1 || MAX_VALUE < in1);
    bool in2c = (0>in2 || MAX_VALUE < in2);
    bool out1c = (0>out1 || MAX_VALUE < out1);
    bool out2c = (0>out2 || MAX_VALUE < out2);

    if ( ( in1c || in2c || out1c || out2c ) || (in2 <= in1 || out2 <= out1) )
        throw std::invalid_argument("Wrong parameters in AdjustContrast");

    double primer_tramo=(double)out1/ (double)in1;
    double segundo_tramo=((double)out2-(double)out1)/((double)in2-(double)in1);
    double tercer_tramo=((double)MAX_VALUE-(double)out2)/((double)MAX_VALUE-(double)in2);
    byte pixel;

    for (int k=0; k < size(); ++k){

        pixel = this->get_pixel(k);
        if(pixel < in1){
            this->set_pixel(k,round(primer_tramo* pixel));
        }

        else if(pixel <= in2){

            this->set_pixel(k,round(out1 + segundo_tramo*(pixel - in1)));
        }
        else if( pixel <= MAX_VALUE){
            this->set_pixel(k,round(out2 + tercer_tramo*(pixel-in2)));
        }
    }

}

void Image::ShuffleRows()
{
    const int p = 9973;
    byte** aux = new byte* [this->get_rows()]; // Copia de las filas de la imagen

    for(int i = 0; i < this->get_rows(); ++i) aux[i] = img[i];

    // Realizamos el barajado

    for(int row = 0; row < this->get_rows(); ++row) {

        int nueva_fila = (row*p) % this->get_rows();
        img[row] = aux[nueva_fila];
    }

    delete [] aux;
    aux = nullptr;

}

////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////

bool operator==(const Image & i1, const Image & i2){
    bool iguales=true;

    if((i1.get_rows()!=i2.get_rows())||(i1.get_cols()!=i2.get_cols())) iguales=false;
    else{
        for(int k=0; k<i1.get_rows()*i1.get_cols(); ++k){
            if(i1.get_pixel(k)-i2.get_pixel(k) != 0) iguales = false;
        }
    }
    return iguales;
}