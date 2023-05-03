const byte cols[] = {2, 3, 4, 5};
const int colCount = sizeof(cols) / sizeof(cols[0]);

const byte rows[] = {6, 7, 8};
const int rowCount = sizeof(rows) / sizeof(rows[0]);

const int keyCount = colCount * rowCount;

int keys[rowCount][colCount];

void handleKeyPress(int index)
{
    Serial.print("Key pressed: ");
    Serial.println(index);

    delay(100);
}

void readKeysMatrix()
{
    for (int colIndex = 0; colIndex < rowCount; colIndex++)
    {
        byte curCol = rows[colIndex];
        pinMode(curCol, OUTPUT);
        digitalWrite(curCol, LOW);
        for (int rowIndex = 0; rowIndex < colCount; rowIndex++)
        {
            byte rowCol = cols[rowIndex];
            pinMode(rowCol, INPUT_PULLUP);
            keys[colIndex][rowIndex] = digitalRead(rowCol);
            if (digitalRead(rowCol) == 0)
                handleKeyPress(rowIndex + (colIndex * sizeof(cols)));
            pinMode(rowCol, INPUT);
        }
        pinMode(curCol, INPUT);
    }
}

void setup()
{
    Serial.begin(9600);

    while (!Serial)
        true;
}

void loop()
{
    readKeysMatrix();
}