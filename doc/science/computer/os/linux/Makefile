OUTDIR = $(shell pwd)
TEX = pdflatex -shell-escape -interaction=nonstopmode -file-line-error
PDFOUT = mastering_linux
PDF_TARGET = $(addsuffix .pdf, $(PDFOUT)) 
LATEXIN = main.tex

all: pdf

pdf: $(addsuffix .pdf, $(PDFOUT))

$(PDF_TARGET): $(LATEXIN)
	echo $(addsuffix .pdf, $(PDFOUT))
	$(TEX) -output-directory=$(OUTDIR) -jobname=$(PDFOUT) $(LATEXIN)
	echo "cleaning .aux and .log"
	rm -f $(addsuffix .log, $(PDFOUT)) $(addsuffix .aux, $(PDFOUT))
	echo "coping to web server"
	sudo cp $(PDF_TARGET) /var/www/html/pdf/

clean web:
	sudo rm /var/www/html/pdf/$(PDF_TARGET)
	
clean:
	rm  -f *.pdf *.aux *.dvi *.log
