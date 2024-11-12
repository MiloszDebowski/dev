class HistogramWorker implements Runnable {
    private Obraz obraz;
    private int startSymbol;
    private int endSymbol;

    public HistogramWorker(Obraz obraz, int startSymbol, int endSymbol) {
        this.obraz = obraz;
        this.startSymbol = startSymbol;
        this.endSymbol = endSymbol;
    }

    @Override
    public void run() {
        obraz.calculate_histogram_parallel_block(startSymbol, endSymbol);
    }
}
