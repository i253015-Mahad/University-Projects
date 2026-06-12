// ----------------------------------------------------------
// 1. Console Log: Page Loaded
// ----------------------------------------------------------
console.log("Homepage loaded successfully");


// ----------------------------------------------------------
// 2. Alert: Login Form Validation
// ----------------------------------------------------------
const loginBtn = document.getElementById("loginBtn");
if (loginBtn) {
    loginBtn.addEventListener("click", function () {
        let email = document.getElementById("email").value;
        let password = document.getElementById("password").value;

        if (email === "" || password === "") {
            alert("Please fill all required fields before logging in.");
        }
    });
}


// ----------------------------------------------------------
// 3. Alert: Add to Cart Confirmation
// ----------------------------------------------------------
const addToCartBtn = document.getElementById("addToCart");
if (addToCartBtn) {
    addToCartBtn.addEventListener("click", function () {
        alert("Product added to cart successfully!");
    });
}


// ----------------------------------------------------------
// 4. Alert: Remove Item from Cart
// ----------------------------------------------------------
const removeItemBtn = document.getElementById("removeItem");
if (removeItemBtn) {
    removeItemBtn.addEventListener("click", function () {
        alert("Are you sure you want to remove this item?");
    });
}


// ----------------------------------------------------------
// 5. Console Log: Search Query Tracking
// ----------------------------------------------------------
const searchBtn = document.getElementById("searchBtn");
if (searchBtn) {
    searchBtn.addEventListener("click", function () {
        const input = document.getElementById("searchInput").value;
        console.log("User searched for:", input);
    });
}


// ----------------------------------------------------------
// 6. Console Log: Category / Filter Selection
// ----------------------------------------------------------
const filterDecor = document.getElementById("filterDecor");
if (filterDecor) {
    filterDecor.addEventListener("click", function () {
        console.log("Category selected: Decor");
    });
}
