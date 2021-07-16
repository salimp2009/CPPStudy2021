#pragma once
#include "RangesPCH.hpp"
#include "Formatting/StockIndex.hpp"

// THIS DOES NOT COMPILE at all!!!!
template<>
struct std::formatter<StockIndex>
{
    enum class IndexFormat { Normal, Short, WithPlus };

    IndexFormat indexFormat{ IndexFormat::Normal };
    // will be used std::locale for localized formatting
    bool localized = false; 

    constexpr auto parse(std::format_parse_context& ctx)
    {
        auto it = ctx.begin();
     
        // helper to search character
        auto isChar = [&](char c)
        {
            if ((it != ctx.end()) && (*it == c))
            {
                ++it;
                return true;
            }
            return false;
        };

        if (isChar('L')) { localized = true; }
        if (isChar('s'))
        {
            indexFormat = IndexFormat::Short;
        }
        else if (isChar('p'))
        {
            indexFormat = IndexFormat::WithPlus;
        }

        // check if at the end of the range
        if (it != ctx.end() && (*it != '}'))
        {
            throw std::format_error("invalid format!");
        }

        // returning an iterator past the end of the parsed range ??; 
        // TODO: check if this should be end-1
        return it;
    }

    auto format(const StockIndex& index, std::format_context& ctx)
    {
        const std::string locFloat{ localized ? "L" : "" };

        const std::string plus{ indexFormat == IndexFormat::WithPlus ? "+" : "" };
               
        if (IndexFormat::Short == indexFormat)
        {
            const auto fmt = std::format("{{:10}}  {{:>8.2{}f}}", locFloat );
            return std::format_to(ctx.out(), fmt, index.name(), index.points());
        }
        else
        {
            const std::string fmt =std::format( "{{:10}} {{:>8.2{0}f}} {{:>{1}7.2{0}f}} {{:{1}.2{0}f}}%", locFloat, plus );

            return std::format_to(ctx.out(), fmt, index.name(), index.points(), index.pointsDiff(), index.pointsPercent());
        }
    }
};
