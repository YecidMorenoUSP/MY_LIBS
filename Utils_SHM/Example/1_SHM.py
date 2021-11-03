from ctypes import *
import ctypes

class SharedBuffer_def(ctypes.Structure):
    _fields_ = [("A",ctypes.c_int32),     #     int A;
                ("B",ctypes.c_float),     #     float B;
                ("C",ctypes.c_char*20)]   #     char C[20];

SharedBuffer = SharedBuffer_def(10,1.0,b"Hola")

print("Size of Shared Buffer :  %d \n"%(sizeof(SharedBuffer)))


SHM_name = "testSHM3"

from multiprocessing import shared_memory, resource_tracker
shm = shared_memory.SharedMemory(name=SHM_name, size=sizeof(SharedBuffer), create=False)
# resource_tracker.unregister(shm._name, 'shared_memory')

# SharedBuffer.from_buffer_copy(shm.buf)

ctypes.memmove(ctypes.addressof(SharedBuffer), shm.buf.tobytes(), sizeof(SharedBuffer))

print(SharedBuffer.A)
print(SharedBuffer.B)
print(SharedBuffer.C)

SharedBuffer.A = 1000

# ctypes.memcpy(shm.buf, SharedBuffer, sizeof(SharedBuffer))

shm.buf[:] = SharedBuffer[:]

shm.close()  
shm.unlink()