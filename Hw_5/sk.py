"""Esqueleto punto 1
pasos
1. sacar datos
2. sacar por columnas
3. calcular fourier
4. espectro de potencias
	a. norma al cuadrado de xmoño
	b. graficar
5. buscar 10 mayores
6. reconstrucción de señales a partir de esos
	a. fourier inverso
	b. graficar
7. chi 2
"""
import numpy as np
import matplotlib as plt
"""
Functions for exercise 1 hw 5
Author: Juan Estupiñán
"""

def getdata (filename):
    """
    load the data in the given file

    in: filename
    out: numpyarray with the data
    """
    n = 10;
    m = 100;
    data = np.ones((n,m))
    return data

    
def getcolumn(data, n):
    """
    returns the column given of the array of data

    in: narray the array
        n the column wanted
    out: ndarray column (single electrode data)
    """
    column = data[:,n]
    return column


def fouriercol (electrode, x):
    """
    returns the fourier transform of a single electrode

    in: ndarray electrode
        x array of times
    out: ndarray FFT_x fourier transform  
         ndarray frecx frecuencies
    """
    n  = 10 #length of array
    dt = 10 #samples
    FFT_x = fft(electrode) / n
    frecx = fftfreq(n, dt) 
    return FFT_x, frecx


def espectrop(FFT_x):
    """
    for a fourier transform, calculates its squared norm
    
    in: ndarray FFT, 
    out: ndarray squared norm of all the components of FFT
    """
    return FFT_x


def searchmax (sqnorm, Frecx):
    """
    selects the 10 maximum norms of the array of norms
    
    in: ndarray sqnorm
        ndarray FrecFFT, frecuencies of fft
    out: ndarray of 10 max norms
         ndarray of 10 frecuencies, corresponding to the positios of the max norms
    """
    x = linspace (1,10)
    y = linspace (1,10)
    return x, y

def reconstruct (maxnorm, Frecx):
    """
    reconstructs the signal doing a inverse fourier transform of the max norms
    
    in: ndarray maxnorm
        ndarray Frecx
    out: ndarray ReconsSignal the reconstructed signal
    """
    x = linspace (1,10)
    return x

def plotsig (ReconSig, electrode):
    """
    plots the reconstructed signal and the original
    
    in: ReconSig, the reconstructed signal
        electrode, the original signal
    """
    plt.plot (ReconSig)
    plt.plot (electrode)
    plt.show

def chisq (ReconSig, electrode):
    """
    calculates the chi squared of the reconstruction
    
    in: ReconSig, the reconstructed signal
        electrode, the original signal
    out: Chi2, the chi squared of a signal
    """
    return 0
