import Button from "../components/Button";
import React, { useEffect, useState } from "react";
import { FormattedMessage } from "react-intl";
import RequiredOptions, {
  RequiredOptionsData,
} from "../components/configuration/RequiredOptions";
import AdvancedOptions, {
  AdvancedOptionsData,
} from "../components/configuration/AdvancedOptions";
import ApiService from "../service/ApiService";
import { CircularProgress } from "@mui/material";

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
    setLoading(true);
    console.log(data);
    ApiService.fetch("/config", "PATCH", {
      type: requiredOptions.type,
      password: requiredOptions.password,
      txPower: data.txPower,
      LoRaSpreadFactor: data.LoRaSpreadFactor,
      bandwidth: data.bandwidth,
      crc: false,
      codingRate: 5,
    }).then((r) => {
      setConfigStep(configStep + 1);
      setLoading(false);
    });
  };

  useEffect(() => {
    setLoading(true);
    ApiService.fetch("/config", "GET").then((config) => {
      setRequiredOptions({
        type: config.type,
        password: config.password,
      });
      setAdvancedOptions({
        txPower: config.txPower,
        LoRaSpreadFactor: config.LoRaSpreadFactor,
        bandwidth: config.bandwidth,
      });
      setLoading(false);
    });
  }, []);

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

      {loading && (
        <>
          <div className="grid gap-4 mt-4 items-left text-left mx-auto">
            <CircularProgress color="warning" />
          </div>
        </>
      )}

      {!loading &&
        {
          [ConfigSteps.REQUIRED_OPTIONS]: (
            <RequiredOptions
              data={requiredOptions}
              onContinue={handleNextRequiredOptions}
            />
          ),
          [ConfigSteps.ADVANCED_OPTIONS]: (
            <AdvancedOptions
              data={advancedOptions}
              onContinue={handleNextAdvancedOptions}
            />
          ),
          [ConfigSteps.DONE]: (
            <>
              <p className="mt-4 text-2xl font-bold">
                <FormattedMessage defaultMessage={"Done"} id={"Done"} />
              </p>

              <div className="grid w-1/2 gap-4 mt-4 items-left text-left mx-auto">
                <p className="">
                  <FormattedMessage
                    defaultMessage={"Configuration done."}
                    id={"Configuration done"}
                  />
                </p>

                <Button
                  onClick={() => {
                    window.location.href = "#/";
                  }}
                  className="mt-6"
                >
                  <FormattedMessage defaultMessage={"Go back"} id={"Go back"} />
                </Button>
              </div>
            </>
          ),
          // [ConfigSteps.TESTING]: <RequiredOptions />,
        }[configStep]}

      <a href="/" className="hover:scale-105 transition-all mt-6 hover:text-red-600 text-red-400 font-bold underline">
        <FormattedMessage defaultMessage={"Cancel"} id={"Cancel"}/>
      </a>
    </>
  );
}
