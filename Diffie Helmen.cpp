#include <bits/stdc++.h>
using namespace std;
using int64 = long long;

// Function to check if a number is prime
bool isPrime(int64 n) {
    if (n <= 1) 
	 return false;
    if (n <= 3) 
	 return true;
    if (n % 2 == 0 || n % 3 == 0) 
	 return false;
    for (int64 i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0)
            return false;
    }
    return true;
}

// Function to compute (base^exp) % mod efficiently
int64 mod_pow(int64 base, int64 exp, int64 mod) {
    base %= mod;
    int64 result = 1 % mod;
    while (exp > 0) {
        if (exp & 1)
            result = (result * base) % mod;
        base = (base * base) % mod;
        exp >>= 1;
    }
    return result;
}

// Function to find all prime factors of n
vector<int64> prime_factors(int64 n) {
    vector<int64> factors;
    if (n % 2 == 0) {
        factors.push_back(2);
        while (n % 2 == 0) n /= 2;
    }
    for (int64 i = 3; i * i <= n; i += 2) {
        if (n % i == 0) {
            factors.push_back(i);
            while (n % i == 0) n /= i;
        }
    }
    if (n > 2) factors.push_back(n);
    return factors;
}

// Check if g is a primitive root modulo p
bool isPrimitiveRoot(int64 g, int64 p) {
    if (g <= 1 || g >= p) return false;
    int64 phi = p - 1;
    vector<int64> factors = prime_factors(phi);

    for (int64 q : factors) {
        if (mod_pow(g, phi / q, p) == 1)
            return false; // Not a primitive root
    }
    return true;
}

int main() {
    cout << "=== Diffie-Hellman Key Exchange Demo ===\n";

    int64 p, g;
    cout << "Enter a prime number p: ";
    if (!(cin >> p)) 
	 return 0;

    if (!isPrime(p)) {
        cout << "Error: " << p << " is not a prime number.\n";
        return 0;
    }

    cout << "Enter base g: ";
    if (!(cin >> g)) 
	 return 0;

    if (p <= 3) {
        cout << "Error: p should be a prime > 3.\n";
        return 0;
    }

    if (!isPrimitiveRoot(g, p)) {
        cout << "Error: " << g << " is NOT a primitive root modulo " << p << ".\n";
        return 0;
    } else {
        cout << g << " is a valid primitive root modulo " << p << ".\n";
    }

    // ✅ Manual private key input
    int64 a, b;
    cout << "\nEnter private key of user A (a): ";
    cin >> a;
    cout << "Enter private key of user B (b): ";
    cin >> b;

    if (a <= 0 || b <= 0 || a >= p || b >= p) {
        cout << "Error: Private keys must be between 1 and " << p - 1 << ".\n";
        return 0;
    }

    // Compute public keys
    int64 A = mod_pow(g, a, p);
    int64 B = mod_pow(g, b, p);

    // Compute shared secrets
    int64 secret1 = mod_pow(B, a, p);
    int64 secret2 = mod_pow(A, b, p);

    // Display results
    cout << "\n=== Results ===\n";
    cout << "Public key of A (A = g^a mod p): " << A << "\n";
    cout << "Public key of B (B = g^b mod p): " << B << "\n";
    cout << "Shared secret (computed by A): " << secret1 << "\n";
    cout << "Shared secret (computed by B): " << secret2 << "\n";

    if (secret1 == secret2)
        cout << "\nSuccess! Shared secrets match.\n";
    else
        cout << "\nError! Shared secrets differ.\n";

    return 0;
}
