/*
 GRT MIT License
 Copyright (c) <2012> <Nicholas Gillian, Media Lab, MIT>
 
 Permission is hereby granted, free of charge, to any person obtaining a copy of this software 
 and associated documentation files (the "Software"), to deal in the Software without restriction, 
 including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, 
 and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, 
 subject to the following conditions:
 
 The above copyright notice and this permission notice shall be included in all copies or substantial 
 portions of the Software.
 
 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT 
 LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. 
 IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, 
 WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE 
 SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#include "FrequencyDomainFeatures.h"

namespace GRT{
    
//Register the FrequencyDomainFeatures module with the FeatureExtraction base class
RegisterFeatureExtractionModule< FrequencyDomainFeatures > FrequencyDomainFeatures::registerModule("FrequencyDomainFeatures");

FrequencyDomainFeatures::FrequencyDomainFeatures(UINT fftWindowSize, UINT hopSize, UINT numDimensions,
                            UINT fftWindowFunction, bool computeMaxFreqFeature, bool computeMaxFreqSpectrumRatio,
                            bool computeCentroidFeature, bool computeTopNFreqFeatures, UINT N) {
    classType = "FrequencyDomainFeatures";
    featureExtractionType = classType;

    infoLog.setProceedingText("[FrequencyDomainFeatures]");
    warningLog.setProceedingText("[WARNING FrequencyDomainFeatures]");
    errorLog.setProceedingText("[ERROR FrequencyDomainFeatures]");

    fft = FFT(fftWindowSize, hopSize, numDimensions, fftWindowFunction, true, false);
    fftf = FFTFeatures(fftWindowSize/2, numDimensions, computeMaxFreqFeature, computeMaxFreqSpectrumRatio,
                       computeCentroidFeature, computeTopNFreqFeatures, N);
}

FrequencyDomainFeatures::FrequencyDomainFeatures(const FrequencyDomainFeatures &rhs){
    infoLog.setProceedingText("[FrequencyDomainFeatures]");
    warningLog.setProceedingText("[WARNING FrequencyDomainFeatures]");
    errorLog.setProceedingText("[ERROR FrequencyDomainFeatures]");

    //Invoke the equals operator to copy the data from the rhs instance to this instance
    *this = rhs;
}
    
FrequencyDomainFeatures::~FrequencyDomainFeatures(void){
}
    
FrequencyDomainFeatures& FrequencyDomainFeatures::operator=(const FrequencyDomainFeatures &rhs){

    if( this != &rhs ){
        this->fft = rhs.fft;
        this->fftf = rhs.fftf;
    }
    return *this;
}

//Clone method
bool FrequencyDomainFeatures::deepCopyFrom(const FeatureExtraction *featureExtraction){ 
    if( featureExtraction == NULL ) return false;

    if( this->getFeatureExtractionType() == featureExtraction->getFeatureExtractionType() ){
        //Invoke the equals operator to copy the data from the rhs instance to this instance
        *this = *(FrequencyDomainFeatures*)featureExtraction;
        return true;
    }

    errorLog << "clone(FeatureExtraction *featureExtraction) -  FeatureExtraction Types Do Not Match!" << endl;
    return false;
}

bool FrequencyDomainFeatures::saveModelToFile(ostream &file) const{
  return false;
}

bool FrequencyDomainFeatures::loadModelFromFile(istream &file){
  return false;
}

bool FrequencyDomainFeatures::computeFeatures(const VectorDouble &inputVector){
  if (!fft.computeFeatures(inputVector)) {
    errorLog << "computeFeatures(const VectorDouble &inputVector) - computing fft failed" << endl;
    return false;
  }

  if (!fftf.computeFeatures(fft.getFeatureVector())) {
    errorLog << "computeFeatures(const VectorDouble &inputVector) - computing fft failed" << endl;
    return false;
  }


  featureDataReady = true;
  featureVector = fftf.getFeatureVector();

  return true;
}

bool FrequencyDomainFeatures::clear(){
  //Clear the base class
  FeatureExtraction::clear();
  fft.clear();
  fftf.clear();
  return true;
}

bool FrequencyDomainFeatures::reset(){ 
  return fftf.reset() && fft.reset();
}

}//End of namespace GRT
