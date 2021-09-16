"""
贪婪算法：每一步都找最优解

任务：让站台覆盖所有城市
（集合覆盖问题）
"""


def make_dictionary_of_stations():
    dictionary_of_stations = {
        "一号站": {"无锡", "南京"},
        "二号站": {"无锡", "南通"},
        "三号站": {"镇江", "上海"},
        "四号站": {"南通", "南京"},
        "五号站": {"苏州", "杭州"}
    }
    return dictionary_of_stations


def find_total_cities(dictionary_of_stations):
    total_cities = []
    for target_station in dictionary_of_stations:
        for city in dictionary_of_stations[target_station]:
            total_cities.append(city)
    total_cities = set(total_cities)
    return total_cities


def find_best_stations(dictionary_of_stations):
    best_stations = []
    cities_needed = find_total_cities(dictionary_of_stations)
    while cities_needed:
        number_of_cities_covered = 0
        best_station = None
        cities_covered = None
        for station, cities in dictionary_of_stations.items():
            if len(cities_needed & cities) > number_of_cities_covered:
                cities_covered = cities_needed & cities
                number_of_cities_covered = len(cities_covered)
                best_station = station
        best_stations.append(best_station)
        cities_needed -= cities_covered
    return best_stations


if __name__ == '__main__':
    stations = make_dictionary_of_stations()
    print("站台表一览：" + str(stations))
    print("可以选择的站台为：" + str(find_best_stations(stations)))
