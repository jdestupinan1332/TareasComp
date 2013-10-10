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
    return

    
def getcolumn(data, n):
    """
    returns the column given of the array of data

    in: narray the array
        n the column wanted
    out: ndarray column (single electrode data)
    """
    return


def fouriercol (electrode, x):
    """
    returns the fourier transform of a single electrode

    in: ndarray electrode
        x array of times
    out: ndarray FFT_x fourier transform  
         ndarray frecx frecuencies
    """
    return


def espectrop(FFT_x):
    """
    for a fourier transform, calculates its squared norm
    
    in: ndarray FFT, 
    out: ndarray squared norm of all the components of FFT
    """
    return


def searchmax (sqnorm, Frecx):
    """
    selects the 10 maximum norms of the array of norms
    
    in: ndarray sqnorm
        ndarray FrecFFT, frecuencies of fft
    out: ndarray of 10 max norms
         ndarray of 10 frecuencies, corresponding to the positios of the max norms
    """
    return

def reconstruct (maxnorm, Frecx):
    """
    reconstructs the signal doing a inverse fourier transform of the max norms
    
    in: ndarray maxnorm
        ndarray Frecx
    out: ndarray ReconsSignal the reconstructed signal
    """
    return

def plotsig (ReconSig, electrode):
    """
    plots the reconstructed signal and the original
    
    in: ReconSig, the reconstructed signal
        electrode, the original signal
    """

def chisq (ReconSig, electrode):
    """
    calculates the chi squared of the reconstruction
    
    in: ReconSig, the reconstructed signal
        electrode, the original signal
    out: Chi2, the chi squared of a signal
    """
    return
