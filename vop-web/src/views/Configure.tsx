import Button from "../components/Button";
import React, { useState } from "react";
import { FormattedMessage } from "react-intl";
import RequiredOptions, {
  RequiredOptionsData,
} from "../components/configuration/RequiredOptions";
import AdvancedOptions, {
  AdvancedOptionsData,
} from "../components/configuration/AdvancedOptions";

export enum ConfigSteps {
  REQUIRED_OPTIONS = 0,
  ADVANCED_OPTIONS = 1,
  DONE = 2,
  //TESTING = 2,
}

export default function Configure() {
  const [loading, setLoading] = useState<boolean>(true);

  const [configStep, setConfigStep] = useState<ConfigSteps>(
    ConfigSteps.REQUIRED_OPTIONS
  );

  const [requiredOptions, setRequiredOptions] = useState<RequiredOptionsData>(
    {}
  );
  const [advancedOptions, setAdvancedOptions] = useState<AdvancedOptionsData>(
    {}
  );

  const handleNextRequiredOptions = (data: RequiredOptionsData) => {
    setRequiredOptions(data);
    setConfigStep(configStep + 1);
  };

  const handleNextAdvancedOptions = (data: AdvancedOptionsData) => {
    setAdvancedOptions(data);
    setConfigStep(configStep + 1);
  };

  return (
    <>
      <h1 className="text-4xl font-bold">
        <FormattedMessage
          id={"Node configuration"}
          defaultMessage={"Node configuration"}
        />
      </h1>

      <p className="mt-4">
        <FormattedMessage
          defaultMessage={
            "Please follow the steps below to configure this node."
          }
          id={"welcomeconfig"}
        />
      </p>

      {
        {
          [ConfigSteps.REQUIRED_OPTIONS]: (
            <RequiredOptions onContinue={handleNextRequiredOptions} />
          ),
          [ConfigSteps.ADVANCED_OPTIONS]: (
            <AdvancedOptions onContinue={handleNextAdvancedOptions} />
          ),
          [ConfigSteps.DONE]: (
            <>
              <p className="mt-4 text-2xl font-bold">
                <FormattedMessage
                  defaultMessage={"Done"}
                  id={"Done"}
                />
              </p>

              <div className="grid w-1/2 gap-4 mt-4 items-left text-left mx-auto">
                <p className="">
                  <FormattedMessage
                    defaultMessage={"Configuration done"}
                    id={"Configuration done"}
                  />
                </p>
                
                <Button
                  onClick={() => {window.location.href = "#/"}}
                  className="mt-6"
                >
                  <FormattedMessage
                    defaultMessage={"Go back"}
                    id={"Go back"}
                  />
                </Button>
              </div>
            </>
          ),
          // [ConfigSteps.TESTING]: <RequiredOptions />,
        }[configStep]
      }
    </>
  );
}
