function range(a, b) {
    const start = Math.min(a, b);
    const end = Math.max(a, b);
    const length = end - start + 1;
    return Array.from({ length }, (_, i) => start + i).sort((x, y) => (a > b ? -1 : 1));
}

// Exemples de tests
console.log(range(1, 5));  // [1, 2, 3, 4, 5]
console.log(range(5, 1));  // [5, 4, 3, 2, 1]
console.log(range(3, 3));  // [3]
