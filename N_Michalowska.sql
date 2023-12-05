-- Zadanie 1.

DROP PROCEDURE IF EXISTS zad1;

DELIMITER $$

CREATE PROCEDURE zad1(
    IN
    _imieK varchar(45),
    _nazwiskoK varchar(45)
)

BEGIN

SELECT
    zamowienia.NumerZamowienia,
    zamowienia.DataZamowienia,
    produkty.NazwaProduktu
FROM zamowienia
JOIN dane_zamowien
ON dane_zamowien.NumerZamowienia = zamowienia.NumerZamowienia
JOIN produkty
ON produkty.NumerProduktu = dane_zamowien.NumerProduktu
JOIN klienci
ON zamowienia.IDKlienta = klienci.IDKlienta
WHERE klienci.ImieKlienta = _imieK
AND klienci.NazwiskoKlienta = _nazwiskoK;

END$$

DELIMITER ;

CALL zad1("Suzanne","Viescas");
-- CALL zad1("Manuela","Seidel");



-- Zadanie 2.

DROP PROCEDURE IF EXISTS zad2;

DELIMITER $$

CREATE PROCEDURE zad2(
    IN
    _dataStart date,
    _dataKoniec date
)

BEGIN

SET @max = (SELECT COUNT(*) wartosc
            FROM zamowienia
            WHERE zamowienia.DataZamowienia > _dataStart
            AND zamowienia.DataZamowienia < _dataKoniec
            GROUP BY zamowienia.IDKlienta
            ORDER BY wartosc
            DESC LIMIT 1
);

CREATE TEMPORARY TABLE temp
AS SELECT klienci.IDKlienta,
COUNT(klienci.IDKlienta) wartosc
FROM klienci
JOIN zamowienia
ON klienci.IDKlienta = zamowienia.IDKlienta
WHERE zamowienia.DataZamowienia > _dataStart
AND zamowienia.DataZamowienia < _dataKoniec
GROUP BY klienci.IDKlienta
HAVING wartosc = @max;

SELECT
	klienci.ImieKlienta,
	klienci.NazwiskoKlienta
FROM klienci
WHERE klienci.IDKlienta
IN (SELECT temp.IDKlienta FROM temp);

END $$

DELIMITER ;

CALL zad2("2012-10-01","2012-10-31");
