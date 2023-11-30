import serial
import time
from tkinter import *
from tkinter import ttk
string1 = "L"
slider1 = 0
slider2 = 0

def fing_hapt1():
        print("Finger 1")
        slider1 = w1.get()
        message = fing1.get() +"," + str(slider1) + "," + "0" + "\n" 
        print(message)
        connect.write(message.encode())

def fing_hapt2():
        print("Finger 2")
        slider1 = w1.get()
        message = fing2.get() +"," + str(slider1) + "," + "0" + "\n" 
        print(message)
        connect.write(message.encode())

def fing_hapt3():
        print("Finger 3")
        slider1 = w1.get()
        message = fing3.get() +"," + str(slider1) + "," + "0" + "\n" 
        print(message)
        connect.write(message.encode())

def fing_hapt(value):
        print(value)
        fing_hapt1()
        fing_hapt2()
        fing_hapt3()

connect = serial.Serial('COM10', 9600)
print("Reset Arduino")
time.sleep(3)

root = Tk()

root.geometry("550x200") #140
root.title("Haptic control")

start_x=600
start_y=50
step=120

side = Label(root, text="PWM").place(x=20, y=120)
w1 = Scale(root, from_=0, to=255, tickinterval= 25, orient=HORIZONTAL, length=400, resolution=5, command=fing_hapt)
w1.set(200)
w1.place(x=80, y=100)

fing1 = StringVar(value="L1")
on_fing1 = ttk.Radiobutton(root, text='on_fing1', variable=fing1, value="H1", command=fing_hapt1)
off_fing1 = ttk.Radiobutton(root, text='off_fing1', variable=fing1, value="L1", command=fing_hapt1)
on_fing1.place(x=130, y=20)
off_fing1.place(x=130, y=50)

fing2 = StringVar(value="L2")
on_fing2 = ttk.Radiobutton(root, text='on_fing2', variable=fing2, value="H2", command=fing_hapt2)
off_fing2 = ttk.Radiobutton(root, text='off_fing2', variable=fing2, value="L2", command=fing_hapt2)
on_fing2.place(x=230, y=20)
off_fing2.place(x=230, y=50)

fing3 = StringVar(value="L3")
on_fing3 = ttk.Radiobutton(root, text='on_fing3', variable=fing3, value="H3", command=fing_hapt3)
off_fing3 = ttk.Radiobutton(root, text='off_fing3', variable=fing3, value="L3", command=fing_hapt3)
on_fing3.place(x=330, y=20)
off_fing3.place(x=330, y=50)

root.mainloop()