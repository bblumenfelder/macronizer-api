FROM python:3.7-stretch
WORKDIR /
COPY requirements.txt /
RUN pip install -r requirements.txt
ADD . /
CMD ["uwsgi", "app.ini"]
COPY /latin-macronizer /latin-macronizer
RUN apt install -y \
    build-essential \
    libfl-dev \
    python3-psycopg2 \
    postgresql
RUN -u postgres psql \
    && create user theusername password 'thepassword'; \
    && create database macronizer encoding 'UTF8' owner theusername; \
    && \q
RUN python macronize.py --initialize
RUN python macronize.py --test