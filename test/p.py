#!/usr/bin/env python3

"""
Node converts joystick inputs into commands for Turtlesim
"""

from tkinter import Button
import rospy
from geometry_msgs.msg import Twist
from sensor_msgs.msg import Joy

def joy_listener():

    # start node
    rospy.init_node("nerimaJoy", anonymous=True)

    # subscribe to joystick messages on topic "joy"
    rospy.Subscriber("/joy", Joy, tj_callback, queue_size=1)

    # keep node alive until stopped
    rospy.spin()

# called when joy message is received
def tj_callback(data):

    # start publisher of cmd_vel to control Turtlesim
    pub = rospy.Publisher("/cmd_vel", Twist, queue_size=1)

    # Create Twist message & add linear x and angular z from left joystick
    twist = Twist()
    twist.linear.x = data.axes[0]
    twist.linear.y = data.axes[1]
    if data.buttons[4] == 1:
        twist.angular.z = -1
    elif data.buttons[5] == 1:
        twist.angular.z = 1

    # record values to log file and screen
    rospy.loginfo("twist.linear.x: %f ; twist.linear.y %f", twist.linear.x, twist.linear.z)

    # publish cmd_vel move command
    pub.publish(twist)
    rate = rospy.Rate(10)
    while not rospy.is_shutdown:
        rate.sleep()

if __name__ == '__main__':
    try:
        joy_listener()
    except rospy.ROSInterruptException:
        pass