#pragma once

#include<cstddef>
#include<iostream>
#include<iterator>
#include<map>

template <typename Int = int>
struct interval_map_t{

    void insert(Int min, Int max);

    void print() const;

    // iterate through intervals
    auto begin() { return map.begin();  }
    auto end()   { return map.end();    }
    auto cbegin(){ return map.cbegin(); }
    auto cend()  { return map.cend();   }

    std::size_t size(){ return map.size(); }

private:
    std::map<Int, Int> map;
};

using interval_map = interval_map_t<int>;

template <typename Int>
void interval_map_t<Int>::insert(Int min, Int max){

    // if max < min print error but continue
    if (max < min){
        std::cout << "Waring: inserted invalid range into interval_map (max < min)\n";
        return;
    } 

    // get iterator to next range
    auto next_it = map.upper_bound(min);

    // if next range is first, add to map
    if (next_it == map.begin()){ map[min] = max; }
    // check if prev range intersects
    else{
        auto prev_it = std::prev(next_it);

        // prev_it contians new, return
        if (prev_it->second > max){ return; }

        // prev_it intersects
        if (prev_it->second >= min){ min = prev_it->first; }
    }

    // remove ranges contained in new range 
    while (next_it != map.end()){

        if (max >= next_it->first){
            if (max < next_it->second){ max = next_it->second; }
            next_it = map.erase(next_it);
        }
        else{ break; }
    }

    // add new range
    map[min] = max;
}

template <typename Int>
void interval_map_t<Int>::print() const{

    for (const auto& range : map){
        std::cout << range.first << "<->" << range.second << "   ";
    }

    std::cout << std::endl;
}