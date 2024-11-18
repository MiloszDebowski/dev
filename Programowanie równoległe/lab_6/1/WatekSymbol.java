class WatekSymbol extends Thread {
    private final Obraz obraz;
    private final char symbol;

    public WatekSymbol(Obraz obraz, char symbol) {
        this.obraz = obraz;
        this.symbol = symbol;
    }

    @Override
    public void run() {
        obraz.calculate_histogram_parallel(symbol);
        obraz.print_histogram_parallel(symbol);
    }
}
