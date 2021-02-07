OUTDIR = $(shell pwd)
TEX = pdflatex -shell-escape -interaction=nonstopmode -file-line-error
PDFOUT = how_to_latex 
PDF_TARGET = $(addsuffix .pdf, $(PDFOUT)) 
LATEXIN = main.tex

all: pdf

pdf: $(PDF_TARGET)

$(PDF_TARGET): $(LATEXIN)
	$(TEX) -output-directory=$(OUTDIR) -jobname=$(PDFOUT) $(LATEXIN)
	$(TEX) -output-directory=$(OUTDIR) -jobname=$(PDFOUT) $(LATEXIN)
	echo "cleaning .aux and .log"
	rm -f $(addsuffix .log, $(PDFOUT)) $(addsuffix .aux, $(PDFOUT)) $(addsuffix .out, $(PDFOUT)) 
	rm -f $(addsuffix .toc, $(PDFOUT)) $(addsuffix .tdo, $(PDFOUT))
	echo "coping to web server"
	sudo cp $(PDF_TARGET) /var/www/html/pdf/
	echo -e "\033[0;32m Target Made Successfully \033[0m"

delete web:
	sudo rm /var/www/html/pdf/$(PDF_TARGET)
	
clean:
	rm  -f *.pdf *.aux *.dvi *.log *.toc *.tdo
