#pragma once
#include "bar_serving.h"
#include <functional>

/**
 * @todo Implement functor-generator that will return next beer brand (cyclic)
 * @example HoeGaarden -> Corona -> Carlsberg -> Bud -> ZlataPraha -> Leffe -> HoeGaarden...
 */
struct BeerOrganizer
{
    BeerBrand operator()() {
        if (++index == static_cast<size_t>(BeerBrand::Max)) {
            index = 1;
        }
        return static_cast<BeerBrand>(index);
    }
private:
    size_t index = 0;
};

/**
 * @todo Implement unary predicate function that will determine if beer is expensive
 * @return true in case if beer is expensive, false if not
 *
 * @note Only Corona and HoeGaarden are expensive
 */
bool isExpensiveBeer(BeerBrand beerBrand)
{
    return beerBrand == BeerBrand::Corona || beerBrand == BeerBrand::HoeGaarden;
}

/**
 * @todo Implement lambda beer country equality comparator
 * @return true if beer county is the same, false otherwise
 */
auto sameCountry = [](BeerBrand l, BeerBrand r)
{
    return getBeerCountry(l) == getBeerCountry(r);
};

struct MixingPolicy
{
    /**
     * @todo Implement static transformator function
     * @return crafted cocktail
     *
     * @note Cookbook:
     * Gin + Lime juice = Gimlet;
     * Gin + Grapefruit juice = Greyhount;
     * Whiskey + SevenUp = SevenPlusSeven;
     * Others + Others = Oops;
     */
    static Cocktail mix(AlcoholDrink alcDrink, NonAlcoholDrink nonAlcDrink)
    {
        switch(alcDrink)
        {
            case AlcoholDrink::Gin:
                if(nonAlcDrink == NonAlcoholDrink::LimeJuice) {
                    return Cocktail::Gimlet;
                }
                if(nonAlcDrink == NonAlcoholDrink::GrapefruitJuice) {
                    return Cocktail::Greyhount;
                }
                break;
            case AlcoholDrink::Whiskey:
                if (nonAlcDrink == NonAlcoholDrink::SevenUp) {
                    return Cocktail::SevenPlusSeven;
                }
                break;
            default:
                break;
        }

        return Cocktail::Oops;
    }
};

std::function<Cocktail(AlcoholDrink, NonAlcoholDrink)> mixer {&MixingPolicy::mix};