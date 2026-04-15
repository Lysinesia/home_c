using System;

namespace ElectroWorld.Models
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