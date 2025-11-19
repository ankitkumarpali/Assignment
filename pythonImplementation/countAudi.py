import pandas as pd 


class GenerateAudiCount:
    def __init__(self, data):
        # print("Data: ", data.columns)
        self.data = data
        self.data['sale_date'] = pd.to_datetime(self.data['sale_date'])
        self.data['sale_year'] = self.data['sale_date'].dt.year

    def calculate_revenue_audi(self, carBrand, sale_year, country):
        self.audi_detail_2025 = self.data[(self.data['manufacturer'] == carBrand) & (self.data['sale_year'] == sale_year) & (self.data['country'] == country)]
        self.total_audi_sold = len(self.audi_detail_2025['sale_price_usd'])
        return self.total_audi_sold