using System;
using System.Collections.Generic;
using System.Text;

namespace Samorukov.Models
{
    public class Product
    {
        public int Id { get; set; }
        public string Name { get; set; } = string.Empty;
        public string Description { get; set; } = string.Empty;
        public decimal Price { get; set; }
        public decimal DiscountPercent { get; set; }
        public decimal FinalPrice => Price - (Price * DiscountPercent / 100);
        public string ImagePath { get; set; } = string.Empty;
    }
}
