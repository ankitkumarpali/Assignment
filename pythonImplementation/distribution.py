import pandas as pd
from countAudi import GenerateAudiCount
from revenueBMW import GenerateBMWRevenue

class DistributionEuropeanCountries:
    def __init__(self, data):
        self.data = data
        self.CarSoldPerCountry = {}
        self.carRevenuePerCountry = {}

    def filter_european_countries(self, region):
        self.filter_european_countries = self.data[self.data['region'] == region]['country'].unique().tolist()
        self.european_countries_df = self.data[self.data['region'] == region]
        self.manufacturer_list = self.data['manufacturer'].unique().tolist()    
        
    def calculate_revenue_per_country(self, manufacturer, country):
        filter_revenue_country = self.data[(self.data['manufacturer'] == manufacturer) & (self.data['country'] == country)]
        revenue = filter_revenue_country['sale_price_usd'].sum()
        return revenue

    def revenue_calculation_europe(self, year):

        # Loop through each country in the European countries list (slow one)

        # for country in self.filter_european_countries:
        #     totalRevenue = 0
        #     for manufacturer in self.manufacturer_list:
        #         # print("Manufacturer: ", manufacturer)
        #         totalRevenue += self.calculate_revenue_per_country(manufacturer, year, country)
        #     self.carRevenuePerCountry[country] = totalRevenue


        # Faster one using pandas groupby
        self.carRevenuePerCountry = self.european_countries_df.groupby('country', )['sale_price_usd'].sum().sort_values(ascending=False)
        return self.carRevenuePerCountry


 