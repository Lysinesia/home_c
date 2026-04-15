using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TechStoreApp
{
    public class Product
    {
        public int Id { get; set; }
        public string Name { get; set; } = "";
        public string Description { get; set; } = "";
        public double Price { get; set; }
        public double DiscountPercent { get; set; }
        public string ImagePath { get; set; } = "";

        public double FinalPrice => Price * (1 - DiscountPercent / 100.0);
        public bool HasDiscount => DiscountPercent > 0;
    }
}