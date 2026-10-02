// Get the display element
const display = document.getElementById("display");


// Add value to the display
function appendValue(value) {

    display.value += value;

}


// Clear the display
function clearDisplay() {

    display.value = "";

}


// Delete the last character
function deleteLast() {

    display.value =
        display.value.slice(0, -1);

}


// Perform calculation
function calculate() {

    try {

        if (display.value === "") {
            return;
        }

        display.value = eval(display.value);

    }

    catch (error) {

        display.value = "Error";

    }

}
