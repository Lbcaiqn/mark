#需要安装的包: pywin32 numpy opencv-python pyautogui
import win32api
import win32con
import win32gui
import win32ui
import win32process
#前台操作推荐使用此库，跨平台并有简单的图色功能，但没有后台
import pyautogui as pg
#颜色，图片，文字识别
import numpy as np
import cv2
#python自带的库
import time

#延时函数 time.sleep(整数)  单位秒
#测试代码运行时间
# t1=time.time()
# 测试代码
# t2=time.time()
# print(t2-t1)

#坐标#
#每个像素点对应一个坐标，左上角为(0,0)，右下角为(分辨率宽-1，分辨率高-1)

#前台操作#
#操作你的鼠标键盘，会影响计算机的正常使用，推荐使用pyautogui库
#后台操作
#虚拟鼠标键盘操作，不影响计算机的正常使用，通过调同Windows API实现
#过程：获取窗口句柄-后台键鼠操作

#父窗口#
#一个进程的窗口全部内容
#子窗口#
#父窗口下的若干窗口
#窗口标题#
#窗口最顶部的字符串，一般只有父窗口有
#窗口类名#
#同名的一类窗口
#窗口句柄#
#唯一标识窗口的ID，是一切窗口操作的基础

#注意，以下函数实参为0不一定代表0，可能代表none或False


#--------------------窗口--------------------#

#-----获取窗口句柄-----#
#1、得到坐标(0,0)所在窗口的句柄,若该坐标在子爽口，则直接获得子窗口句柄
handle=win32gui.WindowFromPoint((0,0))
#2、用窗口类名或窗口标题，从父窗口往下找句柄,必须有一个，另一个设为none
handle=win32gui.FindWindow(0,u'新建文本文档 (3).txt - 记事本')
#3、枚举出父窗口的全部子窗口
def childHandle(handle):
  #参数：父窗口句柄
  #返回：子窗口句柄的列表
  wndList=[]
  win32gui.EnumChildWindows(handle,lambda hwnd,p:p.append(hwnd),wndList)
  return wndList
#-----窗口操作-----#
#由句柄获取窗口标题
win32gui.GetWindowText(handle)
#由句柄获取窗口类名
win32gui.GetClassName(handle)
#返回该窗口在屏幕上的位置，[左,上,右,下]
win32gui.GetWindowRect(handle)
#锁定窗口，前台键鼠无法操作。一些窗口使用此函数无效(如浏览器)
win32gui.EnableWindow(handle,False)
#必须在程序结束时来这一行解除锁定，否则程序结束窗口依然会锁定
win32gui.EnableWindow(handle,True)
#移动主窗口,移动后窗口左上角坐标为(1200,200)
win32gui.SetWindowPos(handle, 0, 1200,200,0,0,win32con.SWP_NOSIZE)
#最小化
win32gui.ShowWindow(handle,win32con.SW_SHOWMINIMIZED)
#最大化
win32gui.ShowWindow(handle,win32con.SW_SHOWMAXIMIZED)





#--------------------键鼠--------------------#

#-----常用操作-----#
#当按下 右方向键 时，返回True，否则返回False，常用来结束死循环
win32api.GetAsyncKeyState(win32con.VK_RIGHT)
#返回坐标(1000,700)的十六进制RGB数组 [R,G,B]
pg.screenshot().getpixel((1000,700))

#-----前台键鼠-----#
#这里是调用winapi，也可以用pyautogui，比winapi好用很多
def clickLeft(x,y):
  win32api.SetCursorPos([x,y])
  win32api.mouse_event(win32con.MOUSEEVENTF_LEFTDOWN,x,y,0,0)
  win32api.mouse_event(win32con.MOUSEEVENTF_LEFTUP,x,y,0,0)

def clickRight(x,y):
  win32api.SetCursorPos([x,y])
  win32api.mouse_event(win32con.MOUSEEVENTF_RIGHTDOWN,x,y,0,0)
  win32api.mouse_event(win32con.MOUSEEVENTF_RIGHTUP,x,y,0,0)

#-----后台键鼠-----#
def backClickLeft(cx,cy,handle):
  mlPosition=win32api.MAKELONG(cx,cy)
  win32api.SendMessage(handle,win32con.WM_LBUTTONDOWN,win32con.MK_LBUTTON,mlPosition)
  time.sleep(0.012) #不知道为什么加了延时速度会快一点
  win32api.SendMessage(handle,win32con.WM_LBUTTONUP,win32con.MK_LBUTTON,mlPosition)

def backClickRight(cx,cy,handle):
  mlPosition=win32api.MAKELONG(cx,cy)
  win32api.SendMessage(handle,win32con.WM_RBUTTONDOWN,win32con.MK_RBUTTON,mlPosition)
  time.sleep(0.012)
  win32api.SendMessage(handle,win32con.WM_RBUTTONUP,win32con.MK_RBUTTON,mlPosition)

def backInput(c,handle):
  win32api.SendMessage(handle,win32con.WM_CHAR,c,0)
  win32api.SendMessage(handle,win32con.WM_CHAR,c,0)
    


#---------------------------图色脚本---------------------------#
#先对窗口截图，再用opencv识别颜色，图片，文字，再键鼠操作
#注意，窗口若被遮挡，最小化，在屏幕外都不行，因为这些情况计算机不会渲染挡住的区域

#-----截图-----#
#代码虽然长，但速度比PIL库快很多
def screensHot(hwnd,dx,dy,width,height):
  #从句柄对应的窗口的坐标(dx,dy)开始，按照宽高截图
  #参数：句柄，距左距离，距上距离，宽，高,
  #返回：四通道RGBA图片

  #申请内存
  hwndDC=win32gui.GetWindowDC(hwnd)
  mfcDC=win32ui.CreateDCFromHandle(hwndDC)
  saveDC=mfcDC.CreateCompatibleDC()
  saveBitmap=win32ui.CreateBitmap()
  #创建位图对象，存储截图信息
  saveBitmap.CreateCompatibleBitmap(mfcDC,width,height)
  saveDC.SelectObject(saveBitmap)
  saveDC.BitBlt((0,0),(width,height),mfcDC,(dx,dy),win32con.SRCCOPY)
  #得到截图的RGBA信息
  imgInfo=saveBitmap.GetBitmapBits(True)
  #释放内存
  win32gui.DeleteObject(saveBitmap.GetHandle())
  saveDC.DeleteDC()
  mfcDC.DeleteDC()
  win32gui.ReleaseDC(hwnd,hwndDC)
  #将上面得到的截图信息转换成一维数组
  img=np.frombuffer(imgInfo,dtype='uint8')
  #将一维数组转换成cv2能识别的格式
  img.shape=(height,width,4)
  #返回RGBA图片
  return img

#展示图片
def imgShow(title,img):
  #参数：图片，标题(字符串)
  #返回：
  cv2.imshow(title,img)
  cv2.waitKey(0)
  cv2.destroyAllWindows()

#返回图片指定像素点的RGBA颜色 (红,绿,蓝,透明度)
def pointRGBA(img,x,y):
  return img[y][x]

#图片识别
#将模板图片在截图上逐像素比较，取相似度最大的
def imgMatch(img,templateLoc):
  #参数：待匹配图片，模板图片路径
  #返回：中心点坐标

  #完整导入模板图片
  template=cv2.imread(templateLoc,cv2.IMREAD_UNCHANGED)
  #灰度化
  img=cv2.cvtColor(img,cv2.COLOR_BGRA2GRAY)
  template=cv2.cvtColor(template,cv2.COLOR_BGRA2GRAY)
  #模板匹配，返回各个位置的匹配度(0到1)，越接近1匹配度越高
  result=cv2.matchTemplate(img,template,cv2.TM_CCORR_NORMED)
  #取出最小值，最大值，最小值位置，最大值位置
  minVal,maxVal,minLoc,maxLoc=cv2.minMaxLoc(result)
  #返回中心点坐标
  h,w=template.shape
  leftTop=maxLoc
  x=leftTop[0]+int(w/2)
  y=leftTop[1]+int(h/2)
  return x,y

#画线
# cv2.rectangle(image,leftTop,rightBottom,(0,0,255),5)


#------------内存----------#

#先用Cheat Engine获得内存基址和偏移量

def modifyMemory(handle,baseAddr,deviation,val):
  #参数：窗口句柄，内存基址，偏移量的列表，修改成的值

  #获取进程ID
  process=win32process.GetWindowThreadProcessId(handle)[1]
  #获取进程句柄
  processHandle=win32api.OpenProcess(0x1F0FFF,False,process)
  #调用windows系统内核
  kernel32=ctypes.windll.LoadLibrary("C:/Windows/System32/kernel32.dll")
  #声明c语言long类型的变量
  pointer=ctypes.c_long()
  #将内存基址赋值给pointer
  kernel32.ReadProcessMemory(int(processHandle),baseAddr,ctypes.byref(pointer),4,None)
  #由内存基址和偏移量计算当前的动态地址的上一级
  for i in deviation[:-1]:
    kernel32.ReadProcessMemory(int(processHandle),pointer.value+i,ctypes.byref(pointer),4,None)
  #修改值
  kernel32.WriteProcessMemory(int(processHandle),pointer.value+deviation[-1],ctypes.byref(ctypes.c_long(val)),4,None)
 

 