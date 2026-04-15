using System;
using System.Collections.Generic;
using System.Text;

namespace Samorukov.Models
{
    public class User
    {
        public int Id { get; set; }
        public string Login { get; set; } = string.Empty;
        public string PasswordHash { get; set; } = string.Empty;
        public int FailedAttempts { get; set; }
        public DateTime? LockedUntil { get; set; }
    }
}
