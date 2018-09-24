FROM node:10.10.0

RUN mkdir -p /home/app
WORKDIR /home/app

# copy package.json & install to cache node_module
COPY package.json yarn.lock /home/app/
RUN yarn install
RUN yarn global add serve

# copy the rest
COPY . /home/app
RUN yarn build