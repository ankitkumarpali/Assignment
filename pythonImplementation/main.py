from countCars import GenerateCarsCount
from revenueCars import GenerateCarsRevenue
from distribution import DistributionEuropeanCountries
import pandas as pd
import time

class Main:

    def __init__(self):
        self.data = pd.read_csv('../world_car_sales_1m.csv')
        # print("Data: ", self.data.columns)
        self.countSoldCar = GenerateCarsCount(self.data)
        self.carRevenue = GenerateCarsRevenue(self.data)
        self.distribution = DistributionEuropeanCountries(self.data)
    
    def run(self):
        self.quantitySoldCar = self.countSoldCar.calculate_car_count('Audi', 2025, 'China')
        self.carRevenueBMW = self.carRevenue.calculate_revenue_cars('BMW', 2025)
        self.EuropeanCountries = self.distribution.filter_european_countries('Europe')
        self.carRevenuePerCountry = self.distribution.cars_revenue_calculation_europe(2025)

        print("Audi Car Sold in 2025 in China: ", self.quantitySoldCar)
        print("BMW Revenue in 2025: ", self.carRevenueBMW)
        print("Car Revenue per Country in 2025 in sorted order: ", self.carRevenuePerCountry)
        # print("Sorted by Revenue: ", self.sortedByRevenue)

if __name__ == '__main__':
    main = Main()
    start_time = time.time()
    main.run()
    end_time = time.time()
    print("Time taken: ", end_time - start_time)

