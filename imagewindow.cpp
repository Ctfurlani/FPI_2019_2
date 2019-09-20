#include "imagewindow.h"
#include <iostream>
#include <QLabel>
#include <QImage>



ImageWindow::ImageWindow(QWidget *parent) : QWidget(parent)
{
    label = new QLabel(this);
    histogram = static_cast<int*>(calloc(256, sizeof (int)));
    histogramWindow = new QWidget();
    equalizedImageWindow = new QWidget();
    equalizedHistogramWindow = new QWidget();
}
void ImageWindow::verticalFlip(){
    uint stride = this->width*3;

    uchar *tmp = static_cast<uchar*>(calloc(stride, sizeof(uchar)));
    for(uint i = 0; i < this->height/2; ++i){
        memcpy(tmp, this->imageData+(i*stride), stride);
        memcpy(this->imageData+(i*stride),this->imageData+(height-i)*stride, stride);
        memcpy(this->imageData+(height-i)*stride, tmp, stride);
    }

    QImage image(this->imageData, this->width, this->height, QImage::Format_RGB888);
    label->setPixmap(QPixmap::fromImage(image));
}

void ImageWindow::horizontalFlip(){
    uint stride = this->width*3;

    uchar *tmp = static_cast<uchar*>(calloc(3, sizeof(uchar)));
    for(uint i = 0; i < this->height; ++i){
        for(uint j = 0; j < stride/2; j+=3){
            memcpy(tmp, this->imageData+(i*stride)+j, 3*sizeof (uchar));
            memcpy(this->imageData+(i*stride)+j, this->imageData+(i*stride)+(stride-j-3), 3*sizeof(uchar));
            memcpy(this->imageData+(i*stride)+(stride-j-3), tmp, 3*sizeof(uchar));
        }
    }
    free(tmp);
    QImage image(this->imageData, this->width, this->height, QImage::Format_RGB888);
    label->setPixmap(QPixmap::fromImage(image));
}

void ImageWindow::greyScale(){
    uchar L;
    uint stride = this->width*3;
    for (uint i=0; i < this->height; ++i){
        for (uint j=0; j < stride; j+=3) {
            uchar R = *(this->imageData+(i*stride)+j);
            uchar G = *(this->imageData+(i*stride)+j+1);
            uchar B = *(this->imageData+(i*stride)+j+2);
            L = static_cast<uchar>(0.299*R+0.587*G+0.114*B);
            R=G=B=L;
            memcpy(this->imageData+(i*stride)+j, &R, sizeof (uchar));
            memcpy(this->imageData+(i*stride)+j+1, &G, sizeof (uchar));
            memcpy(this->imageData+(i*stride)+j+2, &B, sizeof (uchar));
        }
    }
    QImage image(this->imageData, this->width, this->height, QImage::Format_RGB888);
    label->setPixmap(QPixmap::fromImage(image));
}

void ImageWindow::quantization(int quant){
    // eg. quant = 4, partition  = 256/4 = 64
    int partition = 256/quant;
    //Must be done with a grey scale image
    greyScale();
    uint stride = this->width*3;
    for(uint i = 0; i < this->height; ++i){
        for(uint j = 0; j < stride; j+=3){
            // Loads pixel shade
            uchar L = *(this->imageData+(i*stride)+j);
            int q = static_cast<int>(L) + 1;
            // Forces pixel to be of a lesser shade
            for(int w = 1; w <= quant; ++w){
                if( q >= (w-1)*partition and q < w*partition){
                    L = static_cast<uchar>((w-1)*partition);
                }

            }
            // Save quantization
            memcpy(this->imageData+(i*stride)+j, &L, sizeof (uchar));
            memcpy(this->imageData+(i*stride)+j+1, &L, sizeof (uchar));
            memcpy(this->imageData+(i*stride)+j+2, &L, sizeof (uchar));

        }
    }
    QImage image(this->imageData, this->width, this->height, QImage::Format_RGB888);
    label->setPixmap(QPixmap::fromImage(image));
}

/*
    Load JPEG image
    Parameters:
        filename : path of the image
        ori : struct that will have the original image after completion
    Return:
        0 if successful
*/
void ImageWindow::loadImage(char *filename){
    // Struct contains JPEG decompression parameters and pointers
    struct jpeg_decompress_struct cinfo;
    struct jpeg_error_mgr jerr;

    FILE* infile;                       /* Source file */
    JSAMPARRAY buffer;                  /* Output row buffer */
    int row_stride;                     /* Physical row width in output buffer */

    if ( (infile=fopen(filename, "rb"))==nullptr){
        fprintf(stderr, "Can't open %s\n", filename);
        exit(1);
    }
    // Allocate and initialize JPEG decompression object
    cinfo.err = jpeg_std_error(&jerr);

    // Initialise the JPEG decompression object
    jpeg_create_decompress(&cinfo);
    //Specify data source
    jpeg_stdio_src(&cinfo, infile);

    // Read file parameters
    (void) jpeg_read_header(&cinfo, true);

    // Start decompression
    (void) jpeg_start_decompress(&cinfo);
    row_stride = cinfo.output_width * cinfo.output_components;
    buffer = (*cinfo.mem->alloc_sarray)((j_common_ptr) &cinfo, JPOOL_IMAGE, row_stride, 1);

    this->imageData =  static_cast<JSAMPLE*>(calloc(cinfo.output_width*cinfo.output_height*cinfo.output_components, sizeof (JSAMPLE)));
    this->width = cinfo.output_width;
    this->height = cinfo.output_height;

    // Read scanlines, the rows of the image
    int i = 0;
    while (cinfo.output_scanline < cinfo.output_height){
        (void) jpeg_read_scanlines(&cinfo, buffer, 1);
        memcpy(this->imageData+i*row_stride, buffer[0],row_stride);
        ++i;

    }
    // Finish decompression
    (void) jpeg_finish_decompress(&cinfo);

    //Release JPEG decompression object
    jpeg_destroy_decompress(&cinfo);

    fclose(infile);
    if (this->filename == nullptr){
        this->filename = static_cast<char*>( calloc(strlen(filename), sizeof(char)) );
        memcpy(this->filename, filename, strlen(filename)*sizeof (char));

    }

    QImage image(this->imageData, this->width, this->height, QImage::Format_RGB888);
    label->setPixmap(QPixmap::fromImage(image));
    setFixedSize(this->width, this->height);
    //return 0;
}

/*
    Save a JPEG image
    Parameters:
        filename: destination file
        image: struct that contains the jpeg detalis
    Return:
        0 if successful
*/
void ImageWindow::saveImage(char* filename){
    struct jpeg_compress_struct cinfo;
    struct jpeg_error_mgr jerr;

    FILE* outfile;                      /* Target file */
    JSAMPROW row_pointer[1];
    int row_stride;                     /* Physical row width in image buffer*/

    //Allocate and initialise JPEG compression object
    cinfo.err = jpeg_std_error(&jerr);
    jpeg_create_compress(&cinfo);

    // Specify data destination
    if ((outfile = fopen(filename, "wb")) == nullptr){
        fprintf(stderr, "can't open file %s\n", filename);
        exit(1);
    }

    jpeg_stdio_dest(&cinfo, outfile);

    //Set parameters for compression
    cinfo.image_width = this->width;
    cinfo.image_height = this->height;
    cinfo.input_components = 3;
    cinfo.in_color_space = JCS_RGB;

    jpeg_set_defaults(&cinfo);
    jpeg_set_quality(&cinfo, 100, true);
    // Start compressor
    jpeg_start_compress(&cinfo,true);

    row_stride = this->width * 3;
    auto i = 0;
    while (cinfo.next_scanline < cinfo.image_height){
        row_pointer[0] = this->imageData+i*row_stride;
        ++i;
        (void) jpeg_write_scanlines(&cinfo, row_pointer, 1);

    }
    // Finish compression
    jpeg_finish_compress(&cinfo);
    fclose(outfile);
    jpeg_destroy_compress(&cinfo);

    QImage image(this->imageData, this->width, this->height, QImage::Format_RGB888);
    label->setPixmap(QPixmap::fromImage(image));

    //return 0;
}

void ImageWindow::copyImage(){
    loadImage(this->filename);
}

/* Trabalho 2*/
int* ImageWindow::histogramComputation(JSAMPROW data){
    greyScale();
    int *hist = static_cast<int*>( calloc(256, sizeof(int)) );
    for(int i = 0; i < 256; ++i){
        *(hist+i) = 0;
    }

    JDIMENSION stride = this->width*3;
    for(JDIMENSION i = 0; i < this->height; ++i){
        for(JDIMENSION j = 0; j < stride; j+=3){
            *( hist+static_cast<int>(*(data+i*stride+j))) +=1;
        }
    }
    return hist;
}

QImage ImageWindow::showHistogram(int *hist){
    //Normalize histogram to show
    double maximum, weight;
    maximum = *(hist);
    for (int i = 0; i< 256; ++i) {
        if ( *(hist+i) > maximum){
            maximum = *(hist+i);
        }
    }
    weight = 256/maximum;

    uchar *histImage;
    histImage=static_cast<uchar*>( calloc(256*3*256, sizeof(uchar)) );
    int stride = 256*3;
    for(int i = 0; i < 256; ++i){
        int barHeight = static_cast<int>( *(hist+i)*weight);
        for(int j = 0; j < 256; j++){
            if (256-j > barHeight){
                *(histImage+stride*j+3*i) =  255;
                *(histImage+stride*j+3*i+1) =  255;
                *(histImage+stride*j+3*i+2) =  255;
            }
            else{
                *(histImage+stride*j+3*i) =  0;
                *(histImage+stride*j+3*i+1) =  128;
                *(histImage+stride*j+3*i+2) =  255;
            }
        }
    }

    QImage image2(this->imageData, this->width, this->height, QImage::Format_RGB888);
    label->setPixmap(QPixmap::fromImage(image2));
    QImage image(histImage, 256,256, QImage::Format_RGB888);
    return image;


}

void ImageWindow::brightness(int bright){
    uint stride = this->width*3;
    for (uint i=0; i < this->height; ++i){
        for (uint j=0; j < stride; j+=3) {
            int R = *(this->imageData+(i*stride)+j);
            int G = *(this->imageData+(i*stride)+j+1);
            int B = *(this->imageData+(i*stride)+j+2);

            R += bright;
            if (R < 0) R = 0;
            if (R > 255) R = 255;

            G += bright;
            if (G < 0) G = 0;
            if (G > 255) G = 255;

            B += bright;
            if (B < 0) B = 0;
            if (B > 255) B = 255;
            memcpy(this->imageData+(i*stride)+j, &R, sizeof (uchar));
            memcpy(this->imageData+(i*stride)+j+1, &G, sizeof (uchar));
            memcpy(this->imageData+(i*stride)+j+2, &B, sizeof (uchar));
        }
    }

    QImage image(this->imageData, this->width, this->height, QImage::Format_RGB888);
    label->setPixmap(QPixmap::fromImage(image));
}

void ImageWindow::contrast(double cont){
    uint stride = this->width*3;
    for (uint i=0; i < this->height; ++i){
        for (uint j=0; j < stride; j+=3) {
            int R = *(this->imageData+(i*stride)+j);
            int G = *(this->imageData+(i*stride)+j+1);
            int B = *(this->imageData+(i*stride)+j+2);

            R *= cont;
            if (R < 0) R = 0;
            if (R > 255) R = 255;
            R = static_cast<int>(R);

            G *= cont;
            if (G < 0) G = 0;
            if (G > 255) G = 255;
            G = static_cast<int>(G);

            B *= cont;
            B = static_cast<int>(B);
            if (B < 0) B = 0;
            if (B > 255) B = 255;
            memcpy(this->imageData+(i*stride)+j, &R, sizeof (uchar));
            memcpy(this->imageData+(i*stride)+j+1, &G, sizeof (uchar));
            memcpy(this->imageData+(i*stride)+j+2, &B, sizeof (uchar));
        }
    }

    QImage image(this->imageData, this->width, this->height, QImage::Format_RGB888);
    label->setPixmap(QPixmap::fromImage(image));
}

void ImageWindow::negative(){
    uint stride = this->width*3;
    for (uint i=0; i < this->height; ++i){
        for (uint j=0; j < stride; j+=3) {
            int R = *(this->imageData+(i*stride)+j);
            int G = *(this->imageData+(i*stride)+j+1);
            int B = *(this->imageData+(i*stride)+j+2);

            R = 255 - R;
            G = 255 - G;
            B = 255- B;

            memcpy(this->imageData+(i*stride)+j, &R, sizeof (uchar));
            memcpy(this->imageData+(i*stride)+j+1, &G, sizeof (uchar));
            memcpy(this->imageData+(i*stride)+j+2, &B, sizeof (uchar));
        }
    }

    QImage image(this->imageData, this->width, this->height, QImage::Format_RGB888);
    label->setPixmap(QPixmap::fromImage(image));
}

void ImageWindow::equalizeHistogram(){
    //Save current image
    JSAMPROW currData = static_cast<JSAMPROW>(calloc(this->width*this->height*3, sizeof(uchar)));

    int cumulativeHistogram[256];
    double alpha = 255.0/(this->height*this->width);

    this->histogram = histogramComputation(this->imageData);
    QLabel *histLabel = new QLabel(histogramWindow);
    histLabel->setPixmap(QPixmap::fromImage(showHistogram(this->histogram)));
    histogramWindow->setWindowTitle("Original Histogram");
    histogramWindow->setFixedSize(256,256);
    histogramWindow->show();

    // Image just before equalization
    memcpy(currData, this->imageData, sizeof(uchar)*this->width*this->height*3);
    cumulativeHistogram[0] = static_cast<int>(alpha*this->histogram[0]);

    for (int i = 1; i <256 ; ++i){
        cumulativeHistogram[i]= static_cast<int>(cumulativeHistogram[i-1]+alpha*this->histogram[i]);
    }
    uint stride = 3*this->width;
    for (uint i = 0; i < this->height; ++i){
        for (uint j = 0; j < stride; j+=3){
            //R
            *(this->imageData+i*stride+j) = static_cast<uchar>(cumulativeHistogram[*(this->imageData+i*stride+j)]);
            //G
            *(this->imageData+i*stride+j+1) = static_cast<uchar>(cumulativeHistogram[*(this->imageData+i*stride+j+1)]);
            //B
            *(this->imageData+i*stride+j+2) = static_cast<uchar>(cumulativeHistogram[*(this->imageData+i*stride+j+2)]);

         }
    }

    //  Show equalized image in a separate window
    QLabel *eqLabel = new QLabel(equalizedImageWindow);
    QImage image(this->imageData, this->width,this->height, QImage::Format_RGB888);
    eqLabel->setPixmap(QPixmap::fromImage(image));
    equalizedImageWindow->setWindowTitle("Equalized Image");
    equalizedImageWindow->setFixedSize(this->width, this->height);
    equalizedImageWindow->show();

    this->histogram = histogramComputation(this->imageData);
    //  Show equalized histogram
    QLabel *eqHistLabel = new QLabel(equalizedHistogramWindow);
    eqHistLabel->setPixmap(QPixmap::fromImage(showHistogram(this->histogram)));
    equalizedHistogramWindow->setWindowTitle("Equalized Histogram");
    equalizedHistogramWindow->setFixedSize(256,256);
    equalizedHistogramWindow->show();

    //Restores image
    memcpy(this->imageData, currData, sizeof(uchar)*this->width*this->height*3);
    // Update image
    QImage image2(this->imageData, this->width,this->height, QImage::Format_RGB888);
    label->setPixmap(QPixmap::fromImage(image2));
    free(currData);


}

void ImageWindow::imageHistogram(){
    QImage image2(this->imageData, this->width,this->height, QImage::Format_RGB888);
    label->setPixmap(QPixmap::fromImage(image2));

    this->histogram = histogramComputation(this->imageData);
    QLabel *histLabel = new QLabel(histogramWindow);
    histLabel->setPixmap(QPixmap::fromImage(showHistogram(this->histogram)));
    histogramWindow->setWindowTitle("Histogram");
    histogramWindow->setFixedSize(256,256);
    histogramWindow->show();
}

void ImageWindow::histogramMatching(char* filename){
    int *histSrc, *histTarget;
    int *histSrcCumulative, *histTargetCumulative;
    int histMatching[256];

    histSrcCumulative = static_cast<int*>(calloc(256, sizeof(int)));
    histTargetCumulative = static_cast<int*>(calloc(256, sizeof(int)));

    JSAMPROW srcData = static_cast<JSAMPROW>(calloc(this->width*this->height*3, sizeof(uchar)));
    JDIMENSION srcHeight, srcWidth;
    char *srcFile = static_cast<char*>( calloc(strlen(this->filename), sizeof(char)));
    //Compute src and target histograms

    histSrc= histogramComputation(this->imageData);
    // Saves the current image;
    memcpy(srcData, this->imageData, sizeof(uchar)*this->width*this->height*3);
    memcpy(srcFile, this->filename, sizeof(uchar)*strlen(this->filename));
    srcHeight = this->height;
    srcWidth = this->width;

    // Load target to this object
    loadImage(filename);
    histTarget = histogramComputation(this->imageData);

    //Compute src and target normalized cumulative histograms
    double alpha = static_cast<double>(255.0)/(srcWidth*srcHeight);
    memcpy(histSrcCumulative, histSrc, sizeof(int)*256);

    int maximum = *(histSrcCumulative);
    for (int i = 1; i < 256; ++i){
        *(histSrcCumulative+i) = static_cast<int>(*(histSrcCumulative +i-1) + alpha*histSrc[i] );
        if ( *(histSrcCumulative+i) > maximum )
            maximum = *(histSrcCumulative+i);
    }
    /*for (int i = 0; i <256; ++i){
        *(histSrcCumulative+i) = *(histSrcCumulative+i) *255/maximum;
    }*/

    // Target
    alpha = 255.0/(this->width*this->height);
    maximum = *(this->imageData);
    memcpy(histTargetCumulative, histTarget, sizeof(int)*256);
    for (int i = 1; i < 256; ++i){
        *(histTargetCumulative+i) = static_cast<int>(*(histTargetCumulative+i-1)+ histTarget[i] *alpha);
        if ( *(histTargetCumulative+i) > maximum )
            maximum = *(histTargetCumulative+i);
    }

    for (int i = 0; i <256; ++i){
        *(histTargetCumulative+i) = *(histTargetCumulative+i) *255/maximum;
    }

    for (int i = 0; i < 256; ++i){
        int targetShade = closestShade(i, histSrcCumulative, histTargetCumulative);
        histMatching[i] = histTarget[targetShade];
    }

    loadImage(srcFile);
    uint stride = this->width*3;
    for (uint i = 0; i < this->height; ++i){
        for (uint j = 0; j < this->width*3; j+=3){
            *(this->imageData+i*stride+j) = static_cast<uchar>(histMatching[*(srcData+i*stride+j)]);
            *(this->imageData+i*stride+j+1) = static_cast<uchar>(histMatching[*(srcData+i*stride+j)]);
            *(this->imageData+i*stride+j+2) = static_cast<uchar>(histMatching[*(srcData+i*stride+j)]);
        }
    }




    // Show Histograms for debugging
    QLabel *eqHistLabel = new QLabel(histogramWindow);
    eqHistLabel->setPixmap(QPixmap::fromImage(showHistogram(histTargetCumulative)));
    histogramWindow->setWindowTitle("Target Histogram");
    histogramWindow->setFixedSize(256,256);
    histogramWindow->show();

    this->histogram = histogramComputation(this->imageData);
    QLabel *histLabel = new QLabel(equalizedHistogramWindow);
    histLabel->setPixmap(QPixmap::fromImage(showHistogram(histSrcCumulative)));
    equalizedHistogramWindow->setWindowTitle("Matched Histogram");
    equalizedHistogramWindow->setFixedSize(256,256);
    equalizedHistogramWindow->show();

    free(srcData);
    free(srcFile);
    free(histSrcCumulative);
    free(histTargetCumulative);
}

/*
    shade = value of grey shade on src
    src = source cumulative histogram
    target = target cumulative histogram
*/
int ImageWindow::closestShade(int shade, int *src, int *target){
    int targetShade = 0;
    int srcHistCumulativeValue = *(src+shade);
    double distance;
    double previous;
    previous = abs(srcHistCumulativeValue - *target);

    for (int i = 1; i < 256; ++i){
        distance = abs(srcHistCumulativeValue-*(target+i));
        if (distance <= previous){
            previous = distance;
            targetShade = i;
        }
    }

    return targetShade;
}


//trab 2 parte 2
void ImageWindow::zoomOut(int h, int w){
    int stride = this->width*3;

    // New Image
    int newHeight, newWidth;
    newHeight = this->height/h;
    newWidth = this->width/w;
    JSAMPROW newImage = static_cast<JSAMPROW>( calloc(newHeight* newWidth *3, sizeof(uchar)) );
                  //R  G  B
    uchar sum[3] = {0, 0, 0};
    int num = 0;

    for (int i = 0; i < this->height; i+=h) {
        for (int j = 0; j < this->width*3; j+=(w*3)){

            //rectangle
            for (int recLine = 0; recLine < h; ++recLine){
                for (int recColumn = 0; recColumn < w*3; recColumn+=3){
                    if ( (i+recLine < this->height) and (j+recColumn < this->width*3) ){
                        // R channel
                        sum[0] += *( this->imageData + (i+recLine)*stride + j+recColumn );
                        // G channel
                        sum[1] += *( this->imageData + (i+recLine)*stride + j+recColumn + 1 );
                        // B channel
                        sum[2] += *( this->imageData + (i+recLine)*stride + j+recColumn + 2 );
                        ++num;
                    }
                }
            }
            sum[0]/=num;
            sum[1]/=num;
            sum[2]/=num;
            memcpy(newImage+(i/h)*newWidth+j/(3*w), sum, sizeof(uchar)*3);
            sum[0] = sum[1] = sum[2] = num = 0;
        }
    }

    QImage image2(newImage, newWidth,newHeight, QImage::Format_RGB888);
    setFixedSize(newWidth, newHeight);
    label->setPixmap(QPixmap::fromImage(image2));

}





