from countAudi import GenerateAudiCount
from revenueBMW import GenerateBMWRevenue
from distribution import DistributionEuropeanCountries
import pandas as pd

class Main:

    def __init__(self):
        self.data = pd.read_csv('../world_car_sales_1m.csv')
        # print("Data: ", self.data.columns)
        self.countSoldCar = GenerateAudiCount(self.data)
        self.carRevenue = GenerateBMWRevenue(self.data)
        self.distribution = DistributionEuropeanCountries(self.data)
    
    def run(self):
        self.quantitySoldCar = self.countSoldCar.calculate_revenue_audi('Audi', 2025, 'Germany')
        self.carRevenueBMW = self.carRevenue.calculate_revenue_bmw('BMW', 2025)
        self.EuropeanCountries = self.distribution.filter_european_countries('Europe')
        self.carRevenuePerCountry = self.distribution.revenue_calculation_europe(2025)

        print("Audi Car Sold in 2025 in Germany: ", self.quantitySoldCar)
        print("BMW Revenue in 2025: ", self.carRevenueBMW)
        print("Car Revenue per Country in 2025 in sorted order: ", self.carRevenuePerCountry)
        # print("Sorted by Revenue: ", self.sortedByRevenue)

if __name__ == '__main__':
    main = Main()
    main.run()

