# import the necessary packages
from imutils.video import VideoStream
import cv2
import args
import imutils
import time
import picamera
import serial
serial_port = 'dev/ttyACM0' #In this example, using ttyACM0 but this should be changed
                            #if the port you are using is different
serial_baud = 9600
#Initialize serial
ser = serial.Serial(port=serial_port, baudrate=serial_baud, timeout=1)

# define the lower and upper boundaries of the "red"
#need two masks because red "wraps" around 180 in HSV color range
redLower1 = (0, 50, 50)
redUpper1 = (10, 255, 255)
redUpper2 = (170, 50, 50)
redUpper2 = (180, 255, 255)

#start getting video from PiCam
camera = PiCamera()
vs = cv2.VideoCapture(camera)
time.sleep(2.0)

# Algorithm to create masks for red and find x, y coordinates of center
while True:
	# record each frame
	frame = vs.read()
	frame = frame[1] if args.get("video", False) else frame

	# resize the frame, blur it, and convert it to the HSV
	# color space
	frame = imutils.resize(frame, width=600)
	blurred = cv2.GaussianBlur(frame, (11, 11), 0)
	hsv = cv2.cvtColor(blurred, cv2.COLOR_BGR2HSV)

	# construct a mask for the color "red", then perform
	# a series of dilations and erosions
	mask1 = cv2.inRange(hsv, redLower1, redUpper1)
	mask2 = cv2.inRange(hsv, redLower2, redUpper2)
	mask = mask1 + mask2
	mask = cv2.erode(mask, None, iterations=2)
	mask = cv2.dilate(mask, None, iterations=2)
	
	# find contours in the mask and initialize the current
	# (x, y) center of the ball
	cnts = cv2.findContours(mask.copy(), cv2.RETR_EXTERNAL,
		cv2.CHAIN_APPROX_SIMPLE)
	cnts = imutils.grab_contours(cnts)
	center = None

	# only proceed if at least one contour was found
	if len(cnts) > 0:
		# find the largest contour in the mask, then use
		# it to compute the minimum enclosing circle and
		# centroid
		c = max(cnts, key=cv2.contourArea)
		((x, y), radius) = cv2.minEnclosingCircle(c)
		M = cv2.moments(c)
		center = (int(M["m10"] / M["m00"]), int(M["m01"] / M["m00"]))

                #send the data over serial to Arduino to get values of x and y and the radius
                data_to_send = str(x_value) + "," + str(y_value) + "," + str(radius)#prepare string
                ser.write(data_to_send.encode()) #send to serial
                sleep(2)
                
		# only proceed if the radius meets a minimum size
		if radius > 10:
			# draw the circle and centroid on the frame,
			# then update the list of tracked points
			cv2.circle(frame, (int(x), int(y)), int(radius),
				(0, 255, 255), 2)
			cv2.circle(frame, center, 5, (0, 0, 255), -1)

	# show the frame to our screen
	cv2.imshow("Frame", frame)
	key = cv2.waitKey(1) & 0xFF

	# if the 'q' key is pressed, stop the loop
	if key == ord("q"):
		break

# if we are not using a video file, stop the camera video stream
if not args.get("video", False):
	vs.stop()

# otherwise, release the camera
else:
	vs.release()

# close all windows
cv2.destroyAllWindows()
