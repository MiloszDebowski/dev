class WatekSymbol extends Thread {
    private final Obraz obraz;
    private final char symbol;

    public WatekSymbol(Obraz obraz, char symbol) {
        this.obraz = obraz;
        this.symbol = symbol;
    }

    @Override
    public void run() {
        // Oblicz histogram dla danego symbolu
        obraz.calculate_histogram_parallel(symbol);
        // Drukowanie części histogramu dla symbolu
        obraz.print_histogram_parallel(symbol);
    }
}
