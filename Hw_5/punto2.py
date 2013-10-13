import sk2 as sk


def main():
    """
    Reads sunspots data and calculates its period
    """
    #define variables
    inputfile = 'in.out'
    x = linspace(1,10)
    tipe = 'cubic'

    #read data
    data = sk.getdata(inputfile)

    #cleans data
    cleandata(data,x)

    #makes interpolation
    f = sk.interpol(data, x, tipe)
    
    #do fourier
    fft_x , frecx = sk.fourier(f, data, x)

    #potencies spectrum
    sqnorm = sk.espectrop(data)

    #erase some data acording to frecuencies
    sk.erased(frecx, sqnorm)
    
    #do reconstruction
    recondata , reconfrec = sk.reconstruct(sqnorm, frecx)
    
    #plot
    sk.plotdat (recondata, reconfrec)

