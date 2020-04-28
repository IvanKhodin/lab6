import numpy as np
import matplotlib.pyplot as plt

def f(x):
    return (pow(x[0], 2)) + 8 * x[0] + 5 * (pow(x[1], 2)) + 7 * (pow(x[2], 2)) + 119 * x[2] + 531.75
#       (pow(x[0], 2)) + 8 * x[0] + 5 * (pow(x[1], 2)) + 7 * (pow(x[2], 2)) + 119 * x[2] + 531.75
x,y=np.mgrid[-10:10:0.1, -10:10:0.1]
fig,ax0=plt.subplots()
fig,ax1=plt.subplots()
fig,ax2=plt.subplots()
lev_region=[5,10,20,100,150,250,500,750,1000,1250,1500,2000,3000,4000,6000,7000,8000]

cs0=ax0.contour(x, y, f([x,y,0]),levels=lev_region,colors='k')
cs1=ax1.contour(x, y, f([x,0,y]),levels=lev_region,colors='black')
cs2=ax2.contour(x, y, f([0,x,y]),levels=lev_region,colors='black')

ax0.clabel(cs0)
ax1.clabel(cs1)
ax2.clabel(cs2)

inf=[]
with open("traektoria.txt") as tr:
    for line in tr:
        inf.append([float(line.split(',')[0]),float(line.split(',')[1]),float(line.split(',')[2])])
inf=np.array(inf)
ax0.plot(inf[:,0],inf[:,1],"r.-")
ax1.plot(inf[:,0],inf[:,2],"r.-")
ax2.plot(inf[:,1],inf[:,2],"r.-")

ax0.set_title('Linii urovneniya & \n traektoriay poiska \n x1,x2')
ax1.set_title('Linii urovneniya & \n traektoriay poiska \n x1,x3')
ax2.set_title('Linii urovneniya & \n traektoriay poiska \n x2,x3')

plt.show()