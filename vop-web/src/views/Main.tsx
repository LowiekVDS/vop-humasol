import React from "react";
import { FormattedMessage } from "react-intl";
import Button from "../components/Button";

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

      <div className="grid w-1/2 gap-4 mt-16 text-center items-center mx-auto">
        <Button onClick={() => window.location.href = "#/configure"}>
          <FormattedMessage defaultMessage={"configure"} id={"configure"} />
        </Button>
        <Button onClick={() => window.location.href = "#/monitor"}>
          <FormattedMessage defaultMessage={"monitor"} id={"monitor"} />
        </Button>
        <Button className="mt-6" color="error" onClick={() => window.location.href = "#/restart"}>
          <FormattedMessage defaultMessage={"restart"} id={"restart"} />
        </Button>
        <Button className="mt-6" color="error" onClick={() => window.location.href = "#/reset"}>
          <FormattedMessage defaultMessage={"reset"} id={"reset"} />
        </Button>
      </div>
    </>
  );
}

export default MainView;
