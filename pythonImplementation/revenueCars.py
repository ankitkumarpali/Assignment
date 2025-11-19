import pandas as pd

class GenerateCarsRevenue:
    def __init__(self, data):
        self.data = data

    def calculate_revenue_cars(self, carBrand, year):
        self.bmw_detail = self.data[(self.data['manufacturer'] == carBrand) & (self.data['sale_year'] == year)]
        # print("BMW detail: ", self.bmw_detail)
        self.bmw_revenue = self.bmw_detail['sale_price_usd'].sum()
        return self.bmw_revenue