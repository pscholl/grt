/**
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

#ifndef GRT_FrequencyDomainFeatures_HEADER
#define GRT_FrequencyDomainFeatures_HEADER

#include "../../CoreModules/FeatureExtraction.h"
#include "FastFourierTransform.h"
#include "FFT.h"
#include "FFTFeatures.h"

namespace GRT{

class FrequencyDomainFeatures : public FeatureExtraction
{
public:
    /**
     Constructor, sets the fftWindowSize, hopSize, fftWindowFunction, if the magnitude and phase should be computed during the FrequencyDomainFeatures and the number
     of dimensions in the input signal.

     @param UINT fftWindowSize: sets the size of the fft, this should be a power of two. Default fftWindowSize=512
     @param UINT hopSize: sets how often the fft should be computed. If the hopSize parameter is set to 1 then the FrequencyDomainFeatures will be computed everytime
     the classes computeFeatures(...) or computeFrequencyDomainFeatures(...) functions are called. You may not want to compute the FrequencyDomainFeatures of the input signal for every
     sample however, if this is the case then set the hopSize parameter to N, in which case the FrequencyDomainFeatures will only be computed every N samples on the previous M values, where M is equal to the fftWindowSize. Default hopSize=1
     @param UINT numDimensions: the dimensionality of the input data to the FrequencyDomainFeatures.  Default numDimensions = 1
     @param UINT fftWindowFunction: sets the window function of the FrequencyDomainFeatures. This should be one of the FrequencyDomainFeaturesWindowFunctionOptions enumeration values. Default windowFunction=RECTANGULAR_WINDOW
     @param bool computeMaxFreqFeature: sets if the maximum frequency feature will be included in the feature vector. Default value = true
     @param bool computeMaxFreqSpectrumRatio: sets if the maximum-frequency spectrum-frequency ratio feature will be included in the feature vector. Default value = true
     @param bool computeCentroidFeature: sets if the centroid frequency feature will be included in the feature vector. Default value = true
     @param bool computeTopNFreqFeatures: sets if the top N frequency feature will be included in the feature vector. Default value = true
     @param bool N: sets if size of N for the top N frequency features. Default value = 10
     */
    FrequencyDomainFeatures(UINT fftWindowSize=512,
                            UINT hopSize=1,
                            UINT numDimensions=1,
                            UINT fftWindowFunction=FFT::RECTANGULAR_WINDOW,
                            bool computeMaxFreqFeature = true,
                            bool computeMaxFreqSpectrumRatio = true,
                            bool computeCentroidFeature = true,
                            bool computeTopNFreqFeatures = true,
                            UINT N = 10);

    /**
     Copy Constructor, copies the FrequencyDomainFeatures from the rhs instance to this instance

     @param const FrequencyDomainFeatures &rhs: another instance of the FrequencyDomainFeatures class from which the data will be copied to this instance
     */
    FrequencyDomainFeatures(const FrequencyDomainFeatures &rhs);

    /**
     Default Destructor
     */
    virtual ~FrequencyDomainFeatures(void);

    /**
     Sets the equals operator, copies the data from the rhs instance to this instance

     @param const FrequencyDomainFeatures &rhs: another instance of the FrequencyDomainFeatures class from which the data will be copied to this instance
     @return a reference to this instance of FrequencyDomainFeatures
     */
    FrequencyDomainFeatures& operator=(const FrequencyDomainFeatures &rhs);

    /**
     Sets the FeatureExtraction deepCopyFrom function, overwriting the base FeatureExtraction function.
     This function is used to deep copy the values from the input pointer to this instance of the FeatureExtraction module.
     This function is called by the GestureRecognitionPipeline when the user adds a new FeatureExtraction module to the pipeline.

     @param FeatureExtraction *featureExtraction: a pointer to another instance of an FrequencyDomainFeatures, the values of that instance will be cloned to this instance
     @return true if the deep copy was successful, false otherwise
     */
    virtual bool deepCopyFrom(const FeatureExtraction *featureExtraction);

    /**
     Sets the FeatureExtraction computeFeatures function, overwriting the base FeatureExtraction function.
     This function is called by the GestureRecognitionPipeline when any new input data needs to be processed (during the prediction phase for example).
     This function calls the FrequencyDomainFeatures's computeFrequencyDomainFeatures(...) function.

     @param const VectorDouble &inputVector: the inputVector that should be processed.  Must have the same dimensionality as the FeatureExtraction module
     @return true if the data was processed, false otherwise
     */
    virtual bool computeFeatures(const VectorDouble &inputVector);

    /**
     Sets the FeatureExtraction clear function, overwriting the base FeatureExtraction function.
     This function is called by the GestureRecognitionPipeline when the pipelines main clear() function is called.
     This function completely clears the FrequencyDomainFeatures setup, you will need to initialize the instance again before you can use it.

     @return true if the FrequencyDomainFeatures was reset, false otherwise
     */
    virtual bool clear();

    /**
     Sets the FeatureExtraction reset function, overwriting the base FeatureExtraction function.
     This function is called by the GestureRecognitionPipeline when the pipelines main reset() function is called.
     This function resets the FrequencyDomainFeatures by re-initiliazing the instance.

     @return true if the FrequencyDomainFeatures was reset, false otherwise
     */
    virtual bool reset();

    /**
     This saves the feature extraction settings to a file.
     This overrides the saveSettingsToFile function in the FeatureExtraction base class.

     @param fstream &file: a reference to the file to save the settings to
     @return returns true if the settings were saved successfully, false otherwise
     */
    virtual bool saveModelToFile(ostream &file) const;

    /**
     This loads the feature extraction settings from a file.
     This overrides the loadSettingsFromFile function in the FeatureExtraction base class.

     @param fstream &file: a reference to the file to load the settings from
     @return returns true if the settings were loaded successfully, false otherwise
     */
    virtual bool loadModelFromFile(istream &file);

    FFT fft;
    FFTFeatures fftf;
protected:
    static RegisterFeatureExtractionModule< FrequencyDomainFeatures > registerModule;
};

} //End of namespace GRT

#endif //GRT_FrequencyDomainFeatures_HEADER
