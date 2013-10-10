import sk


def main():
    """
    Reads electrocardiogram and do an fourier transform for data analysis
    """
    
    #define variables
    inputfile = 'in.out'
    x = linspace(1,10)
    
    #get data
    data = sk.getdata(inputfile)
    
    #select column of the data we need
    column = sk.getcolumn(data, 0)
    
    # do fourier
    fft_x , freqx = sk.fouriercol (column, x)

    #get potencies spectra
    sqrdnorm = sk.espectrop(fft_x)
    
    #search maximums
    naxnorms , maxfreq = sk.searchmax(sqrdnorm, freqx)
    
    #do the reconstruction
    recon = sk.reconstruct(naxnorms, maxfreq)
    
    #plots
    plotsig(recon, column)
    
    #gives chi2
    n = chisq (recon, column)
    


if __name__ == "__main__":
    main()
