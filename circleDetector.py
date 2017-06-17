
# import the necessary packages
import numpy as np
import argparse
import cv2
import scipy 
 
def imshow_quitter():
	while(True):
		key = cv2.waitKey(0)
		if key == 113 :
			cv2.destroyAllWindows()
			break

# construct the argument parser and parse the arguments
ap = argparse.ArgumentParser()
ap.add_argument("-i", "--image", required = True, help = "Path to the image")
args = vars(ap.parse_args()) 

 
# load the image, clone it for output, and then convert it to grayscale
image = cv2.imread(args["image"])
output = image.copy()

gray = cv2.cvtColor(output, cv2.COLOR_BGR2GRAY)
#gray = cv2.GuassianBlur(gray)j tt

circles = cv2.HoughCircles(gray,cv2.HOUGH_GRADIENT,1,20,
                    param1=50,param2=30,minRadius=0,maxRadius=0)
circle_num = 1
print(circles)
print(gray.size)
# ensure at least some circles were found
if circles is not None:
	# convert the (x, y) coordinates and radius of the circles to integers
	circles = np.round(circles[0, :]).astype("int")
 
	# loop over the (x, y) coordinates and radius of the circles
	for (x, y, r) in circles:
		# draw the circle in the output image, then draw a rectangle
		# corresponding to the center of the circleaf	

		print("ciricles",(x,y,r))
		diameterCircle = int(scipy.pi * r) + 1 
		# Crop cricle from imaged		y1 = y - (r + 3)
		y2 = y + (r + 3)
		x1 = x - (r + 3)
		x2 = x + (r + 3) 
		crop_img = output[y1:y2 , x1:x2]  
		cv2.imwrite("Circle\ "+str(circle_num)+'.jpg',crop_img) 
		cv2.circle(output, (x, y), r, (0, 255, 0), 4)
		n
		cv2.rectangle(output, (x - 5, y - 5), (x + 5, y + 5), (0, 128, 255), -1)
 		circle_num += 1 
	# show the output image
	
	cv2.imshow("output", output) 
	print(output.size,"   ",output.shape)
	imshow_quitter() 
