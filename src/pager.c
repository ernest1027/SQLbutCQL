#include "pager.h"

void *get_page(Pager *pager, uint32_t page_number)
{
    if (page_number > TABLE_MAX_PAGES)
    {
     printf("%d\n", page_number);


        print_pager_error(PAGER_OUT_OF_BOUNDS);
        exit(EXIT_FAILURE);
    }

    if (pager->pages[page_number] == NULL)
    {
        void *page = malloc(PAGE_SIZE);
        uint32_t num_pages = pager->file_length / PAGE_SIZE;
        if (pager->file_length % PAGE_SIZE)
        {
            num_pages += 1;
        }

        if (page_number <= num_pages)
        {
            lseek(pager->file_descriptor, page_number * PAGE_SIZE, SEEK_SET);
            ssize_t bytes_read = read(pager->file_descriptor, page, PAGE_SIZE);
            if (bytes_read == -1)
            {
                print_pager_error(PAGER_FILE_READ_ERROR);
                exit(EXIT_FAILURE);
            }
        }
        pager->pages[page_number] = page;
        if (page_number >= pager->num_pages)
        {
            pager->num_pages = page_number + 1;
        }
    }

    return pager->pages[page_number];
}
Pager *pager_open(char *filename)
{
    int fd = open(filename, O_RDWR | O_CREAT, S_IWUSR | S_IRUSR);
    if (fd == -1)
    {
        print_pager_error(PAGER_FILE_READ_ERROR);
        exit(EXIT_FAILURE);
    }

    off_t file_length = lseek(fd, 0, SEEK_END);

    Pager *pager = malloc(sizeof(Pager));
    pager->file_descriptor = fd;
    pager->file_length = file_length;
    pager->num_pages = (file_length / PAGE_SIZE);
    for (int i = 0; i < TABLE_MAX_PAGES; i++)
        pager->pages[i] = NULL;
    return pager;
}
void page_flush(Pager *pager, uint32_t page_number)
{
    if (pager->pages[page_number] == NULL)
    {
        print_pager_error(PAGER_OUT_OF_BOUNDS);
        exit(EXIT_FAILURE);
    }

    off_t offset = lseek(pager->file_descriptor, page_number * PAGE_SIZE, SEEK_SET);

    if (offset == -1)
    {
        print_pager_error(PAGER_FILE_READ_ERROR);
        exit(EXIT_FAILURE);
    }

    ssize_t bytes_written = write(pager->file_descriptor, pager->pages[page_number], PAGE_SIZE);

    if (bytes_written == -1)
    {
        print_pager_error(PAGER_FILE_READ_ERROR);
        exit(EXIT_FAILURE);
    }
}

uint32_t get_free_page_num(Pager *pager)
{
    return pager->num_pages;
}
