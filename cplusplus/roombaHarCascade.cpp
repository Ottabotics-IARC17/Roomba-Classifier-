/* compilation instructions
 
g++ -ggdb `pkg-config --cflags --libs opencv` roombaHarCascade.cpp -o roombaHarCascade
 
 */



#include <iostream> 
#include <opencv2/opencv.hpp> 

using namespace cv ; 
String roombaCascade_name = "cascade_roomba.xml" ; 
CascadeClassifier roomba_cascade ; 

/* function requires a sourceImage and a 
vector of cv:Rect to store possible candidates of object */
void detect_roomba_HarCascade(Mat&, std::vector<Rect>) ; 

int main( int argc, char** argv ){

	roomba_cascade = roombaCascade_name ; 

	// Load cascasde for simple detection 
	if( !roomba_cascade.load( roombaCascade_name ) ){ 
		printf("--(!)Error loading\n");
		 return -1; 
	};

	// To get video from webcam
	VideoCapture cap(0) ;
    std::cout << cap.isOpened() << std::endl ;
    if (!cap.isOpened()) {
        std::cout << "VideoFile not found /Webcam not opened" << std::endl ;
    }

    Mat orig_frame , gray_frame; 
    // Vector of possible Candidates for a detected roomba
    std::vector<Rect> candidates; 
    
    while(true){

    	cap >> orig_frame ; 
    	if( ! orig_frame.empty()){
    		imshow("DataFromWebcam",orig_frame);
    		detect_roomba_HarCascade(orig_frame,candidates) ;
    	}
   
   	
    //Small delay required at end of loop to display images	
   	 waitKey(1) ; 


    }

}

void detect_roomba_HarCascade(Mat& sourceImage, std::vector<Rect> candidates){
		/* function requires a sourceImage and a 
		vector of cv:Rect to store possible candidates of object */
		Mat sourceImage_gray ;
		if( sourceImage.empty()){
			std::cout << "ERROR sourceImage is empty" << std::endl;
			throw "image is empty, can't detect roombas" ;
		}

		//is image gray ? if not convert it to GRAY
		// assuming is in BGR format (standard for opencv)
		if(sourceImage.channels() != 1){
			cvtColor(sourceImage,sourceImage_gray,CV_BGR2GRAY) ; 
		}else{
			sourceImage_gray = sourceImage ; 
		}
    	
		roomba_cascade.detectMultiScale( sourceImage_gray	, candidates, 1.1, 2, 0|CV_HAAR_SCALE_IMAGE, Size(30, 30) );
    	

    	for(int i = 0 ; i < candidates.size() ; ++i){
    		rectangle(sourceImage,candidates[i],Scalar(0,0,255));
    			
    	}

		imshow("DataFromWebcam",sourceImage) ;
    }







