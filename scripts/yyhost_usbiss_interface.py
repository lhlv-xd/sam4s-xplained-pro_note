# -*- coding: utf-8 -*-
"""
Created on Fri Apr 18 11:33:26 2025

@author: Yuyi_Chen
"""

from usb_iss import UsbIss, defs
from config import *
import time
import math

global I2C_SLAVE_ADDRESS, COMPORT


class UsbIssDriver():
    __instance = None
    def __new__(cls, *args, **kwargs):
        if cls.__instance is None:
            cls.__instance = super().__new__(cls)
            cls.__instance.__initialized = False
        return cls.__instance
    
    def __init__(self):
        ## already init
        if (self.__initialized):
            return
        
        ########################
        ## Init
        ########################
        ## Variable        
        self.__com_port = None
        self.__is_connected = False
        
        ## Instance
        self.__iss = UsbIss()
        
        ## Set         
        self.__initialized = True
        
    def connect(self, com_port=COMPORT, clock_khz=400, use_i2c_hardware=True, baud_rate=115200):
        """ Connection """
        if (self.__is_connected):
            return self
        
        ## Avoid to connect again
        self.__com_port = com_port
        self.__is_connected = True
        
        self.__iss.open(self.__com_port)
        self.__iss.setup_i2c()
        # self.__iss.setup_i2c_serial(clock_khz, use_i2c_hardware, baud_rate)
           
        return self
    
    def close(self):
        """ Disconnection """
        self.__iss.close()
    
    def set_iss(self, handle):
        """ Set usbiss instance """
        self.__iss = handle
        
    def get_iss(self):
        """ Get usbiss instance """
        return self.__iss
    
    
    def __write_i2c(self, slave_address, register, data:list):
        """
        Write data through i2c interface and call function one time
        (data need to be equal or less than 60)
        """
        size = len(data)
        if (size > 60):
            return
        
        self.__iss.i2c.write(slave_address, register, data)
        
        
    def write_i2c(self, slave_address, register, data:list):
        """ 
        Write data through i2c interface
        ( UsbIss limits data size to no more than 60 )
        note: 
            When register less than or equal to 0x7f，if it move to the right by 1, it will be overflow to 0x00.
            When register greater than 0x80，if it move to the right by 0x80, it will be overflow to 0x80.
        """
        size = len(data)
        if (size <= 60):
            self.__write_i2c(slave_address, register, data)
            return
        
        ## If data size is greater than 60, it is divided into several frames.
        frame_nums = math.ceil(size / 60)
        __register = register
        for frame_num in range(frame_nums):
            ## Process
            start, end = frame_num * 60, ((frame_num + 1) * 60) if (((frame_num + 1) * 60) < size) else size
            __register = register + start
            __register = (__register & 0x7f) if (register <= 0x7f) else (0x80 + (__register & 0x7f))
            self.__write_i2c(slave_address, __register, data[start:end])
            
        
    
    def __read_i2c(self, slave_address, register, size):
        """
        Write data through i2c interface and call function one time
        (data need to be equal or less than 60)
        """
        if (size > 60):
            return
        
        return self.__iss.i2c.read(slave_address, register, size)
    
    def read_i2c(self, slave_address, register, size):
        """ 
        Read data through i2c interface
        ( UsbIss limits data size to no more than 60 )
        """
        data = [] 
        if (size <= 60):
            data.extend(self.__read_i2c(slave_address, register, size))
        
        ## data size is greater than 60
        frame_nums = math.ceil(size / 60)
        __register = register
        for frame_num in range(frame_nums):
            ## Process
            start, end = frame_num * 60, ((frame_num + 1) * 60) if (((frame_num + 1) * 60) < size) else size
            __register = register + start
            __register = (__register & 0x7f) if (register <= 0x7f) else (0x80 + (__register & 0x7f))
            data.extend(self.__read_i2c(slave_address, __register, end - start))
        
        
        return data;
        


    

def main(): 
    ## Initialized
    sam4s = UsbIssDriver().connect()

    ## Write Data
    register = 0x00
    data = [i & 0xff for i in range(128)]
    
    sam4s.write_i2c(I2C_SLAVE_ADDRESS, register, data)
    
    
    
    ## Read Data
    recv_data = sam4s.read_i2c(I2C_SLAVE_ADDRESS, 0x7f, 128)
    
    print(recv_data)
    
    ## Close usbiss
    sam4s.close()

    pass


if __name__ == "__main__":
    main()