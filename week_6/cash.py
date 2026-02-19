def get_change():
    while True:
        try:
            dollars = float(input("Change: "))
            if dollars >= 0:
                return dollars
        except ValueError:
            pass

dollars = get_change()
cents = round(dollars * 100)

coins = 0
coin_values = [25, 10, 5, 1]

for coin in coin_values:
    coins += cents // coin
    cents %= coin

print(coins)