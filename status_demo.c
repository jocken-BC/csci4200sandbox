#include <stdio.h>

// Helper function to print an 8-bit byte in binary format for students
void print_binary(const char* label, unsigned char num) {
    printf("%-25s: 0x%02X (Binary: ", label, num);
    for (int i = 7; i >= 0; i--) {
        printf("%d", (num >> i) & 1);
        if (i == 4) printf(" "); // Visual gap between nibbles
    }
    printf(")\n");
}

int main() {
    // Initial state: Error is active (1), Ready is inactive (0), TX is active (1)
    // Bit layout: [Reserved:0000] [Error:1] [Ready:0] [TX:1] [RX:0] = 0x0A
    unsigned char status = 0x0A; 
    
    printf("--- INITIAL HARDWARE STATE ---\n");
    print_binary("Initial Status", status);
    printf("\n");

    /* ======================================================================
     * CONCEPT 1: USING 'AND' (&) TO CLEAR BITS
     * Rule: X & 0 = 0 (Clears bit)  |  X & 1 = X (Preserves bit)
     * ====================================================================== */
    printf("--- TASK 1: CLEAR THE ERROR FLAG (BIT 3) ---\n");
    
    // Mask has 0 at Bit 3, and 1s everywhere else: 1111 0111 (0xF7)
    unsigned char clear_mask = 0xF7; 
    print_binary("AND Mask (0xF7)", clear_mask);
    
    // Apply the AND operation
    status = status & clear_mask; 
    print_binary("Result (Error Cleared)", status);
    printf("\n");

    /* ======================================================================
     * CONCEPT 2: USING 'OR' (|) TO SET BITS
     * Rule: X | 1 = 1 (Sets bit)  |  X | 0 = X (Preserves bit)
     * ====================================================================== */
    printf("--- TASK 2: SET THE READY FLAG (BIT 2) ---\n");
    
    // Mask has 1 at Bit 2, and 0s everywhere else: 0000 0100 (0x04)
    unsigned char set_mask = 0x04; 
    print_binary("OR Mask (0x04)", set_mask);
    
    // Apply the OR operation
    status = status | set_mask; 
    print_binary("Result (Ready Set)", status);
    printf("\n");

    /* ======================================================================
     * CONCEPT 3: USING 'XOR' (^) TO TOGGLE BITS
     * Rule: X ^ 1 = ~X (Flips bit)  |  X ^ 0 = X (Preserves bit)
     * ====================================================================== */
    printf("--- TASK 3: TOGGLE THE TX BUSY FLAG (BIT 1) ---\n");
    
    // Mask has 1 at Bit 1, and 0s everywhere else: 0000 0010 (0x02)
    unsigned char toggle_mask = 0x02;
    print_binary("Current Status", status);
    print_binary("XOR Mask (0x02)", toggle_mask);
    
    // First toggle: Flips TX Busy from 1 to 0
    status = status ^ toggle_mask;
    print_binary("Result 1 (TX Turned OFF)", status);
    
    // Second toggle: Flips TX Busy from 0 back to 1
    status = status ^ toggle_mask;
    print_binary("Result 2 (TX Turned ON)", status);
    printf("\n");

    /* ======================================================================
     * CONCEPT 4: USING 'AND' (&) TO READ / TEST BITS
     * Rule: (X & Mask) evaluates to non-zero if the bit is 1, and 0 if it is 0.
     * ====================================================================== */
    printf("--- TASK 4: TEST IF RX BUSY (BIT 0) OR TX BUSY (BIT 1) ARE SET ---\n");
    
    // Let's explicitly check Bit 0 (RX Busy) using a mask of 0x01
    // Current status has Bit 0 as 0.
    if ((status & 0x01) != 0) {
        printf("  [Result] RX Busy bit is SET (1)\n");
    } else {
        printf("  [Result] RX Busy bit is CLEAR (0)\n");
    }

    // Let's explicitly check Bit 1 (TX Busy) using a mask of 0x02
    // Current status has Bit 1 as 1.
    if ((status & 0x02) != 0) {
        printf("  [Result] TX Busy bit is SET (1)\n");
    } else {
        printf("  [Result] TX Busy bit is CLEAR (0)\n");
    }
    printf("\n");

    /* ======================================================================
     * CONCEPT 5: IDIOMATIC C (SHIFTING TO CREATE MASKS)
     * Real-world code avoids hardcoded hex masks. It shifts 1 into place.
     * ====================================================================== */
    printf("--- BONUS: THE IDIOMATIC C WAY ---\n");
    
    // Resetting status back to initial state for demonstration
    status = 0x0A; 
    
    // Clear bit 3 using bitwise NOT (~) and shift (<<)
    status &= ~(1 << 3);
    print_binary("Cleared Bit 3 with &=", status);
    
    // Set bit 2 using shift (<<)
    status |= (1 << 2);
    print_binary("Set Bit 2 with |=", status);

    // Toggle bit 1 using shift (<<)
    status ^= (1 << 1);
    print_binary("Toggled Bit 1 with ^=", status);

    // Test bit 1 using shift (<<) inside the condition
    if (status & (1 << 1)) {
        printf("  Idiomatic Check: Bit 1 is active!\n");
    }

    return 0;
}