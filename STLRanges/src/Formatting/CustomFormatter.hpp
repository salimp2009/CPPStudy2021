#pragma once
#include "RangesPCH.hpp"
#include "Formatting/StockIndex.hpp"



template<>
struct std::formatter<StockIndex> {
    std::string formatString;


    constexpr auto parse(format_parse_context& ctx) 
    { return ctx.begin(); }

    auto format(const StockIndex& index, format_context& ctx)
    {
        return std::format_to(ctx.out(),
            "{:10}  {:>8.2f}  {:>6.2f} {:.2f}%",
            index.name(),
            index.points(),
            index.pointsDiff(),
            index.pointsPercent());
    }
};