import { Button } from "@mui/material";
import React from "react";
import { FormattedMessage } from "react-intl";

function MainView() {
  return (
    <>
      <h1 className="text-4xl font-bold">
        <FormattedMessage
          id={"What do you want to do?"}
          defaultMessage={"What do you want to do?"}
        />
      </h1>

      <p className="mt-4">
        <FormattedMessage
          defaultMessage={
            "Welcome to the configuration page. Please select what you want to do."
          }
          id={"welcomeconfig"}
        />
      </p>

      <div className="grid grid-cols-2 w-9/12 gap-4 mt-16 text-center items-center mx-auto">
        <a
          href="#/configure"
          className="aspect-square flex bg-amber-300 hover:bg-amber-700 flex-col text-center items-center object-center justify-center"
        >
          <p className="uppercase font-bold">
            <FormattedMessage
              id="configure"
              defaultMessage={"configure"}
            ></FormattedMessage>
          </p>
        </a>
        <a
          href="#/monitor"
          className="aspect-square bg-amber-300 flex hover:bg-amber-700 flex-col text-center items-center object-center justify-center"
        >
          <p className="uppercase font-bold">
            <FormattedMessage
              id="monitor"
              defaultMessage={"monitor"}
            ></FormattedMessage>
          </p>
        </a>
      </div>
    </>
  );
}

export default MainView;
