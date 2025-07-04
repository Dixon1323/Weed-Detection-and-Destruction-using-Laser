from ultralytics import YOLO
import cv2
import math 
import time
import socket
import serial
import streamlit as st

previous_millis=0
interval=3000

ser = serial.Serial('/dev/cu.usbserial-1420', 9600)

st.title("Weed Detection")
image_window = st.image([])
grid_window=st.image([])

st.sidebar.title("Settings")
show_grid = st.sidebar.checkbox("Show Grid", value=False)

cap = cv2.VideoCapture(0)
# cap = cv2.VideoCapture("vid1.mp4")
cap.set(3, 480) #width
cap.set(4, 480) #height   
model = YOLO("best.pt")

classNames = ["weed"]


def find_box(x1, x2, y1, y2, width_parts, height_parts):
    midpoint_x = (x1 + x2) // 2
    midpoint_y = (y1 + y2) // 2
    row = midpoint_y // (height_parts[1] - height_parts[0])
    col = midpoint_x // (width_parts[1] - width_parts[0]) 
    box_number = 1 + row * 16 + col
    return box_number

def calculate_vertical_distance(y2, image_height, scale_factor=1.0):
    # Calculate a vertical distance based on bounding box and scale factor for finer control
    floatdistance_cm = ((image_height - y2) / image_height) * 100 * scale_factor
    distance_cm = int(floatdistance_cm)
    return distance_cm


# def mindist_mqtt(mindist):
#     # data_to_send = str(int(mindist))
#     data_to_send = str(mindist) + ',' + str(selected_box_number)
#     client.publish("nodemcu/data", data_to_send)
#     # time.sleep(5)  # Add a delay between each data publish
#     print("********************************data has been sent from here to nodemcu **************************")


closest_distance = float('inf')
closest_box = None

while True:
    success, img = cap.read()
    if not success:
        st.write("Failed to capture video")
        break
    img_temp=img.copy()
    results = model(img, stream=True)
    midpoint_x = img.shape[1] // 2
    midpoint_y = img.shape[0] // 2
    print("midpoint =",midpoint_x,"midpoint =",midpoint_y)
    height, width, _ = img.shape
    print("Image Width =", width, "Image Height =", height)

    width_parts = [i * (width // 16) for i in range(17)]
    height_parts = [i * (height // 16) for i in range(17)]
    print("widthp =",width_parts,"heightp =",height_parts)

    for i in range(17):
        cv2.line(img_temp, (width_parts[0], height_parts[i]), (width_parts[16], height_parts[i]), (0, 255, 0), 1)

    for i in range(17):
        cv2.line(img_temp, (width_parts[i], height_parts[0]), (width_parts[i], height_parts[16]), (0, 255, 0), 1)

    grid_num = 1
    for i in range(16):
        for j in range(16):
            center_x = (width_parts[j] + width_parts[j + 1]) // 2
            center_y = (height_parts[i] + height_parts[i + 1]) // 2
            cv2.putText(img_temp, str(grid_num), (center_x, center_y),fontFace=cv2.FONT_HERSHEY_SIMPLEX,fontScale=0.5, color=(0, 0, 255), thickness=1)
            grid_num += 1

    # coordinates
    for r in results:
        boxes = r.boxes

        for box in boxes:
            print("-"*90)
            # bounding box
            x1, y1, x2, y2 = box.xyxy[0]
            x1, y1, x2, y2 = int(x1), int(y1), int(x2), int(y2) # convert to int values

            box_number = find_box(x1, x2, y1, y2, width_parts, height_parts)
            print("The midpoint lies in box number:", box_number)
            vertical_distance = calculate_vertical_distance(y2, height)
            if vertical_distance < closest_distance:
                closest_distance = vertical_distance
                closest_box = (x1, y1, x2, y2)
                selected_box_number = find_box(closest_box[0],closest_box[2],closest_box[1],closest_box[3], width_parts, height_parts)
                print("The midpoint of the selected lies in box number:", selected_box_number)
                b=str(selected_box_number)
                print(type(b))
                ser.write(b.encode())
                mindist = vertical_distance = calculate_vertical_distance(y2, height)

            # put box in cam
            cv2.rectangle(img, (x1, y1), (x2, y2), (0, 0, 255), 3)
                
            vertical_distance = calculate_vertical_distance(y2, height)
            print("The object is approximately", vertical_distance, "cm away in the vertical direction.")


            # confidence
            # confidence = math.ceil((box.conf[0]*100))/100
            # print("Confidence --->",confidence)

            # class name
            cls = int(box.cls[0])
            print("Class name -->", classNames[cls])
            a=classNames[cls]
            print(a)

            # object details
            org = [x1, y1]
            org1 = [x1, y1+20]
            org2 = [x1, y1+50]
            font = cv2.FONT_HERSHEY_SIMPLEX
            fontScale = 1
            color = (255, 0, 0)
            thickness = 2

            cv2.putText(img, classNames[cls], org, font, fontScale, color, thickness)
            cv2.putText(img, str(vertical_distance), org1, font, fontScale, color, thickness)
            cv2.putText(img, str(box_number), org2, font, fontScale, (0,255,255), thickness)
            cv2.putText(img, str(mindist), org2, font, fontScale, (0,255,0), thickness)

    if closest_box is not None:
         print("shortest distance is =",mindist)
         x1, y1, x2, y2 = closest_box 
         cv2.rectangle(img, (x1, y1), (x2, y2), (0, 0, 255), 3)
         current_millis=int(round(time.time()*1000))
         print("current_millis =",current_millis)
         if(current_millis-previous_millis>=interval):
             previous_millis=current_millis
             print("in millis delay")
            #  mindist_mqtt(mindist)

         

    closest_distance = float('inf')
    closest_box = None
    img_rgb = cv2.cvtColor(img, cv2.COLOR_BGR2RGB)
    image_window.image(img_rgb)
    if show_grid:
        img_rgb_temp = cv2.cvtColor(img_temp, cv2.COLOR_BGR2RGB)
        image_window.image(img_rgb_temp)

    # cv2.imshow('Webcam', img)
    # cv2.imshow('Grid',img_temp)
    if cv2.waitKey(1) == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()


