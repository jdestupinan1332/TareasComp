"""1. obtener data
  a. limpiar data i.e. quitar datos con -99.0
2. interpolacion
  a. constante
  b. lineal
  c. cubica
3. calcular espectros de potencia i.e. fourier-norma-cuadrado
4. ver que frecuencia es 20 anos y 2 anos, borrar los menores a 20 y mayores a 2
5. con los que queden hacer inverse fourier
6. normalizar
7. plot reconstruccion y original
8. estimar periodo solar
"""

"""
Funtions for exercise 2 hw 5
Author: Juan Estupiann
"""
import numpy as np
import matplotlib as plt
import scipy as scy

def getdata (filename):
    """
    get the data given in the filename

    in: Filename the name of the file
    out:narray data
    """
    n = 10;
    m = 100;
    data = np.ones((n,m))
    return data


def cleandata(data, x):
    """
    search for -99.0 in the column 4 of the data, if found erases the row, do the same for x
    in: data the raw data
        x the frecuencies of months
    """


def interpol(data, x, tipe):
    """
    do interpolation with the numpy rutines
    in: narray data, cleaned
        ndarray x, cleaned
        type, the type of the interpolation wanted
    out:intrpl the interpolation wanted
    """
    f = interp1t(data, x, kind=tipe)
    return f


def fourier(intrpl, data, x):
    """
    makes interpolation and fourier transform of wanted data

    in: intrpl the function that interpoles
        narray data of the sunspots
        array x of times
    out: ndarray FFT_x fourier transform
         ndarray frecx frecuencies
    """
    n  = 10 #length of array
    dt = 10 #samples
    FFT_x = fft(data) / n
    frecx = fftfreq(n, dt) 
    return FFT_x, frecx


def espectrop(FFT_x):
    """
    for a fourier transform, calculates its squared norm
    
    in: ndarray FFT, 
    out: ndarray squared norm of all the components of FFT
    """
    return FFT_x

def erased(Frecx, sqnorms):
    """
    checks what frecuency corresponds to 20 and 2 years, erases the lower and upper of those in the frecuencies and the transform arrays
    
    in: ndarray Frecx, frecuencies
        ndarray sqnorms, squared norms of FFT_x
    """


def reconstruct (sqnorms, Frecx):
    """
    reconstructs the data doing an inverse fourier transform, then normalizes
    
    in: ndarray sqnorms
        ndarray Frecx
    out: ndarray Recondata the reconstructed data
         ndarray Reconfrec the reconstructed frecuencies
    """
    return sqnorms, Frecx


def plotdat(Recondata, Reconfrec):
    """
    plots the reconstructed data
    
    in: Recondata, data for the y axis of plot
        Reconfrec, data for the x axis of plot
    """


