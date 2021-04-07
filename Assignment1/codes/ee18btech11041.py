import soundfile as sf
from scipy import signal
import matplotlib.pyplot as plt
import numpy as np

#if using termux
#import subprocess
#import shlex
#end if


input_signal,fs = sf.read('Sound_Noise.wav')
sample_freq = fs
order = 4
cutoff_freq = 4000.0
Wn = 2*cutoff_freq/sample_freq
b,a = signal.butter(order,Wn, 'low')
output_signal = signal.filtfilt(b,a,input_signal)
sf.write('Sound with Reduced Noise.wav',output_signal,fs)


fig, axs = plt.subplots(2)
axs[0].plot(output_signal)
axs[0].set_title("built-in function")
axs[0].grid()


N = len(input_signal)
w = np.linspace(0,2*np.pi,N)

num = np.polyval(b,np.exp(1j*w))
den = np.polyval(a,np.exp(1j*w))
Hz = num/den

X = np.fft.fft(input_signal)
Y = Hz*X
Y = np.multiply(Hz,X)
y = np.fft.ifft(Y).real

sf.write('7.1_Sound_With_ReducedNoise.wav',y,fs)

axs[1].plot(y,'green')
axs[1].set_title("own routine")
axs[1].grid()

for ax in axs.flat:
    ax.set(xlabel='t', ylabel='y(t)')

for ax in axs.flat:
    ax.label_outer()


plt.savefig('../figs/ee18btech11041_1.eps')
#subprocess.run(shlex.split("termux-open ../figs/ee18btech11041_1.eps"))  #if using termex

freq = np.arange(-np.pi,np.pi,2*np.pi/len(input_signal))


fig, axs = plt.subplots(2)
axs[0].plot(freq,np.abs(np.fft.fftshift(np.fft.fft(output_signal))))
axs[0].set_title("built-in function")
axs[0].grid()



axs[1].plot(freq,np.abs(np.fft.fftshift(np.fft.fft(y))),'green')
axs[1].set_title("own routine")
axs[1].grid()


for ax in axs.flat:
    ax.set(xlabel='w', ylabel='|Y(w)|')

for ax in axs.flat:
    ax.label_outer()

plt.savefig('../figs/ee18btech11041_2.eps')
#subprocess.run(shlex.split("termux-open ../figs/ee18btech11041_2.eps"))  #if using termex
# plt.show()    
