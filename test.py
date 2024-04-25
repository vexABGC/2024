from math import cos, sin, pi

lf_out = 0
lb_out = 0
rf_out = 0
rb_out = 0

#take joystick input
angleRadians = pi/2
deadZone = 0
leftJoyX = 0
leftJoyY = 1
rightJoyX = 0
rightJoyY = 0

strafe = leftJoyY*sin(angleRadians) - leftJoyX*cos(angleRadians)
drive = leftJoyX*sin(angleRadians) + leftJoyY*cos(angleRadians)
print(strafe, drive)

#modify outputs with dead zones and global strafe
lf_out = drive + strafe
lb_out = drive - strafe
rf_out = drive - strafe
rb_out = drive + strafe

print(lf_out, lb_out, rf_out, rb_out)
print(lf_out, lb_out, rf_out, rb_out)

delta_position_x = lf_out + rb_out - lb_out - rf_out
delta_position_y = lf_out + rb_out + lb_out + rf_out
print(lf_out, lb_out, rf_out, rb_out)
print(delta_position_x, delta_position_y)